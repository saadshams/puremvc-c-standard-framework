#include "interfaces/controller.h"
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include "interfaces/view.h"

static Controller *instance;
pthread_mutex_t controller_mutex = PTHREAD_MUTEX_INITIALIZER;

static CommandNode *newCommandNode(const char *notificationName, SimpleCommand*(*commandFactory)()) {
    CommandNode *self = malloc(sizeof(CommandNode));
    self->name = strdup(notificationName);
    self->commandFactory = commandFactory;
    self->next = NULL;
    return self;
}

static void initializeController(Controller *self) {
    self->view = getViewInstance(newView);
}

static void executeCommand(const Controller *self, Notification *notification) {
    CommandNode *cursor = self->commandMap;
    while(cursor != NULL && strcmp(cursor->name, notification->getName(notification)) != 0)
        cursor = cursor->next;

    if (cursor != NULL) {
        SimpleCommand *commandInstance = cursor->commandFactory();
        commandInstance->execute(commandInstance, notification);
    }
}

static void registerCommand(Controller *self, const char *notificationName, SimpleCommand *(commandFactory)()) { // init, return if existing, append
    if(self->commandMap == NULL) { // init
        self->commandMap = newCommandNode(notificationName, commandFactory);
        // register observer
    } else if(!self->hasCommand(self, notificationName)) { // append
        CommandNode *cursor = self->commandMap;
        while(cursor->next != NULL)
            cursor = cursor->next;
        cursor->next = newCommandNode(notificationName, commandFactory);
        // register observer
    } else { // update command only

    }
}

static bool hasCommand(const Controller *self, const char *notificationName) {
    CommandNode *cursor = self->commandMap;
    while(cursor != NULL && strcmp(cursor->name, notificationName) != 0)
        cursor = cursor->next;
    return cursor != NULL;
}

static void removeCommand(Controller *self, const char *notificationName) {
    if(self->commandMap == NULL) return;

    CommandNode *cursor = self->commandMap;
    if(strcmp(self->commandMap->name, notificationName) == 0) { // base case if node is first node
        CommandNode *temp = self->commandMap;
        self->commandMap = temp->next;
    } else {
        while(cursor->next != NULL && strcmp(cursor->next->name, notificationName) != 0)
            cursor = cursor->next;

        if(cursor->next != NULL) {
            CommandNode *temp = cursor->next;
            cursor->next = temp->next;
            temp->next = NULL;
            free(temp);
        }
    }
}

static void release(Controller *self) {
    free(self);
}

Controller *newController() {
    assert(instance == NULL);
    Controller *self = malloc(sizeof(Controller));
    self->base = self;
    self->commandMap = NULL;
    self->initializeController = initializeController;
    self->executeCommand = executeCommand;
    self->registerCommand = registerCommand;
    self->hasCommand = hasCommand;
    self->removeCommand = removeCommand;
    self->release = release;
    instance = self;
    return self;
}

Controller *getControllerInstance(Controller *(controllerFactory)()) {
    pthread_mutex_lock(&controller_mutex);
    if(instance == NULL) {
        instance = controllerFactory();
        instance->initializeController(instance);
    }
    pthread_mutex_unlock(&controller_mutex);
    return instance;
}
