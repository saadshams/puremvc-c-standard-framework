#ifndef PUREMVC_CONTROLLER_H
#define PUREMVC_CONTROLLER_H

#include "simple_command.h"
#include <stdbool.h>

typedef struct CommandNode CommandNode;

struct CommandNode {
    char *name;
    SimpleCommand *(*commandFactory)();
    CommandNode *next;
};

typedef struct Controller Controller;

struct Controller {
    CommandNode *commandMap;
    void *view;
    void (*initializeController)(Controller *self);
    void (*executeCommand)(const Controller *self, Notification *notification);
    void (*registerCommand)(Controller *self, const char *notificationName, SimpleCommand*(*commandFactory)());
    bool (*hasCommand)(const Controller *self, const char *notificationName);
    void (*removeCommand)(Controller *self, const char *notificationName);
    void (*release)(Controller *self);
    Controller *base;
};

Controller *newController();

Controller *getControllerInstance(Controller *(controllerFactory)());

#endif //PUREMVC_CONTROLLER_H