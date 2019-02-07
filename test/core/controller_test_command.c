#include "controller_test_command.h"
#include "controller_test_vo.h"
#include <stdlib.h>

static void execute(const SimpleCommand *self, Notification *notification) {
    ControllerTestVO *vo = (ControllerTestVO *)notification->getBody(notification);
    vo->result = 2 * vo->input;
}

ControllerTestCommand *newControllerTestCommand() {
    ControllerTestCommand *self = malloc(sizeof(ControllerTestCommand));
    self->super.execute = execute;
    return self;
}