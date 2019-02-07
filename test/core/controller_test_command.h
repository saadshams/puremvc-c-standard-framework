#ifndef PUREMVC_CONTROLLER_TEST_COMMAND_H
#define PUREMVC_CONTROLLER_TEST_COMMAND_H

#include "interfaces/simple_command.h"

typedef struct ControllerTestCommand ControllerTestCommand;

struct ControllerTestCommand {
    SimpleCommand super;
};

ControllerTestCommand *newControllerTestCommand();

#endif //PUREMVC_CONTROLLER_TEST_COMMAND_H
