#ifndef PUREMVC_CONTROLLER_TEST_COMMAND2_H
#define PUREMVC_CONTROLLER_TEST_COMMAND2_H

#include "interfaces/simple_command.h"

typedef struct ControllerTestCommand2 ControllerTestCommand2;

struct ControllerTestCommand2 {
    SimpleCommand super;
};

ControllerTestCommand2 *newControllerTestCommand2();

#endif //PUREMVC_CONTROLLER_TEST_COMMAND2_H
