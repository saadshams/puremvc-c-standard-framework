#ifndef PUREMVC_SIMPLE_COMMAND_H
#define PUREMVC_SIMPLE_COMMAND_H

#include "notification.h"

typedef struct SimpleCommand SimpleCommand;

struct SimpleCommand {
    void (*execute)(const SimpleCommand *self, Notification *notification);
    void (*release)(SimpleCommand *self);
    SimpleCommand *base;
};

SimpleCommand *newSimpleCommand();

#endif //PUREMVC_SIMPLE_COMMAND_H
