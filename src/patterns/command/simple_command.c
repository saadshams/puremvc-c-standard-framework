#include "interfaces/simple_command.h"

#include <stdlib.h>

static void execute(const SimpleCommand *self, Notification *notification) {

}

static void release(SimpleCommand *self) {
    free(self);
}

SimpleCommand *newSimpleCommand() {
    SimpleCommand *self = malloc(sizeof(SimpleCommand));
    self->execute = execute;
    self->release = release;
    self->base = self;
    return self;
}
