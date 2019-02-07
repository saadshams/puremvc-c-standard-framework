#include "interfaces/observer.h"
#include <stdlib.h>

static void *getNotifyContext(const Observer *self) {
    return self->context;
}

static void setNotifyContext(Observer *self, void *notifyContext) {
    self->context = notifyContext;
}

static void (*getNotifyMethod(const Observer *self))(Notification *notification) {
    return self->notify;
}

static void setNotifyMethod(Observer *self, void (*notifyMethod)(Notification *notification)) {
    self->notify = notifyMethod;
}

static void notifyObserver(const Observer *self, Notification *notification) {
    self->notify(notification);
}

static bool compareNotifyContext(const Observer *self, const void *object) {
    return self->context == object;
}

static void release(Observer *self) {
    free(self);
}

Observer *newObserver(void *notifyMethod, void *notifyContext) {
    Observer *observer = malloc(sizeof(Observer));
    observer->notify = notifyMethod;
    observer->context = notifyContext;
    observer->getNotifyContext = getNotifyContext;
    observer->setNotifyContext = setNotifyContext;
    observer->getNotifyMethod = getNotifyMethod;
    observer->setNotifyMethod = setNotifyMethod;
    observer->notifyObserver = notifyObserver;
    observer->compareNotifyContext = compareNotifyContext;
    observer->release = release;
    return observer;
}