#include "simple_command_test_command.h"
#include "simple_command_test_vo.h"
#include <stdlib.h>

static void execute(const SimpleCommand *self, Notification *notification) {
    SimpleCommandTestVO *vo = notification->getBody(notification);
    vo->result = 2 * vo->input;
}

static void release(SimpleCommand *self) {
    self->base->release(self->base);
    free(self);
}

SimpleCommandTestCommand *newSimpleCommandTestCommand() {
    SimpleCommandTestCommand *self = malloc(sizeof(SimpleCommand));
    self->super.execute = execute;
    self->super.release = release;
    return self;
}
