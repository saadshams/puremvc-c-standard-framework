#include "interfaces/view.h"
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static View *instance;
pthread_mutex_t view_mutex = PTHREAD_MUTEX_INITIALIZER;

static MediatorNode *newMediatorNode(Mediator *mediator) {
    MediatorNode *self = malloc(sizeof(MediatorNode));
    self->name = strdup(mediator->getMediatorName(mediator));
    self->mediator = mediator;
    self->next = NULL;
    return self;
}

void registerMediator(View *self, Mediator *mediator) { // init, check for re-register, append, onRegister (register observers for each)
    // do not allow re-registration (you must to removeMediator fist)
    if(self->hasMediator(self, mediator->getMediatorName(mediator))) return;

    if(self->mediatorMap == NULL) { // init
        self->mediatorMap = newMediatorNode(mediator);
    } else { // append
        MediatorNode *cursor = self->mediatorMap;
        while(cursor->next != NULL)
            cursor = cursor->next;
        cursor->next = newMediatorNode(mediator);
    }

    // register observers

    mediator->onRegister(mediator);
}

Mediator *retrieveMediator(View *self, const char *mediatorName) {
    MediatorNode *cursor = self->mediatorMap;
    while(cursor != NULL && strcmp(cursor->name, mediatorName) != 0)
        cursor = cursor->next;
    return cursor == NULL ? NULL : cursor->mediator;
}

bool hasMediator(View *self, const char *mediatorName) {
    MediatorNode *cursor = self->mediatorMap;
    while(cursor != NULL && strcmp(cursor->name, mediatorName) != 0)
        cursor = cursor->next;
    return cursor != NULL;
}

Mediator *removeMediator(View *self, const char *mediatorName) {
    if(self->mediatorMap ==  NULL) return NULL;

    Mediator *mediator;
    if(strcmp(self->mediatorMap->name, mediatorName) == 0) { // base case
        MediatorNode *temp = self->mediatorMap;
        self->mediatorMap = temp->next;
        mediator = temp->mediator;
        free(temp);
    } else {
        MediatorNode *cursor = self->mediatorMap;
        while(cursor->next != NULL && strcmp(cursor->next->name, mediatorName) != 0)
            cursor = cursor->next;

        if(cursor->next != NULL) {
            MediatorNode *temp = cursor->next;
            mediator = temp->mediator;
            cursor->next = temp->next;
            free(temp);
        }
    }

    if(mediator != NULL) mediator->onRemove(mediator);

    // remove observers

    return mediator;
}

static void release(View *self) {
    free(self);
}

View *newView() {
    assert(instance == NULL);
    View *self = malloc(sizeof(View));
    self->base = self;
    self->mediatorMap = NULL;
    self->registerMediator = registerMediator;
    self->retrieveMediator = retrieveMediator;
    self->hasMediator = hasMediator;
    self->removeMediator = removeMediator;
    self->release = release;
    instance = self;
    return self;
}

View *getViewInstance(View *(viewFactory)()) {
    pthread_mutex_lock(&view_mutex);
    if(instance == NULL)
        instance = viewFactory();
    pthread_mutex_unlock(&view_mutex);
    return instance;
}