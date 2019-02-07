#ifndef PUREMVC_MACRO_COMMAND_TEST_SUB1_COMMAND_H
#define PUREMVC_MACRO_COMMAND_TEST_SUB1_COMMAND_H

#include "interfaces/simple_command.h"
#include "interfaces/notification.h"

typedef struct MacroCommandTestSub1Command MacroCommandTestSub1Command;

struct MacroCommandTestSub1Command {
    SimpleCommand super;
};

MacroCommandTestSub1Command *newMacroCommandTestSub1Command();

#endif //PUREMVC_MACRO_COMMAND_TEST_SUB1_COMMAND_H