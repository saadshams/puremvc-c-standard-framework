#ifndef PUREMVC_MEDIATOR_H
#define PUREMVC_MEDIATOR_H

#include "notification.h"

typedef struct Mediator Mediator;

struct Mediator {
    char *mediatorName;
    void *viewComponent;
    char *(*getMediatorName)(const Mediator *self);
    void (*setViewComponent)(Mediator *self, void *viewComponent);
    void *(*getViewComponent)(const Mediator *self);
    char **(*listNotificationInterests)(const Mediator *self);
    void (*handleNotification)(const Mediator *self, Notification *notification);
    void (*onRegister)(Mediator *self);
    void (*onRemove)(Mediator *self);
    void (*release)(Mediator *self);
    Mediator *base;
};

static char *MEDIATOR_NAME = "Mediator";

Mediator *newMediator(char *mediatorName, void *viewComponent);

#endif //PUREMVC_MEDIATOR_H
