#include "interfaces/mediator.h"
#include <stdlib.h>
#include <string.h>

static char *getMediatorName(const Mediator *self) {
    return self->mediatorName;
}

static void setViewComponent(Mediator *self, void *viewComponent) {
    self->viewComponent = viewComponent;
}

static void *getViewComponent(const Mediator *self) {
    return self->viewComponent;
}

static char **listNotificationInterests(const Mediator *self) {
    return (char *[]){};
}

static void handleNotification(const Mediator *self, Notification *notification) {

}

static void onRegister(Mediator *self) {

}

static void onRemove(Mediator *self) {

}

static void release(Mediator *self) {
    free(self);
}

Mediator *newMediator(char *mediatorName, void *viewComponent) {
    Mediator *self = malloc(sizeof(Mediator));
    self->base = self;
    self->mediatorName = strdup(mediatorName != NULL ? mediatorName : MEDIATOR_NAME);
    self->viewComponent = viewComponent;
    self->getMediatorName = getMediatorName;
    self->setViewComponent = setViewComponent;
    self->getViewComponent = getViewComponent;
    self->listNotificationInterests = listNotificationInterests;
    self->handleNotification = handleNotification;
    self->onRegister = onRegister;
    self->onRemove = onRemove;
    self->release = release;
    return self;
}