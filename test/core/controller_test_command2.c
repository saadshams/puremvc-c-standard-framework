#include "controller_test_command2.h"
#include "controller_test_vo.h"
#include <stdlib.h>

static void execute(const SimpleCommand *self, Notification *notification) {
    ControllerTestVO *vo = notification->getBody(notification);

    vo->result = vo->result + (2 * vo->input);
}

ControllerTestCommand2 *newControllerTestCommand2() {
    ControllerTestCommand2 *self = malloc(sizeof(ControllerTestCommand2));
    self->super.execute = execute;
    return self;
}