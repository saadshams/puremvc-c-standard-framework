#include "interfaces/notification.h"
#include <stdlib.h>
#include <string.h>

static char *getName(const Notification *self) {
    return self->name;
}

static void setBody(Notification *self, void *body) {
    self->body = body;
}

static void *getBody(const Notification *self) {
    return self->body;
}

static void setType(Notification *self, const char *type) {
    free(self->type);
    self->type = strdup(type);
}

static char *getType(const Notification *self) {
    return self->type;
}

static void release(Notification *self) {
    free(self->name);
    free(self->type);
    self->body = NULL;
    free(self);
}

Notification *newNotification(char *name, void *body, char *type) {
    Notification *self = malloc(sizeof(Notification));
    self->name = name != NULL ? strdup(name) : NULL;
    self->type = type != NULL ? strdup(type) : NULL;
    self->type = type;
    self->body = body;
    self->getName = getName;
    self->setBody = setBody;
    self->getBody = getBody;
    self->setType = setType;
    self->getType = getType;
    self->release = release;
    return self;
}