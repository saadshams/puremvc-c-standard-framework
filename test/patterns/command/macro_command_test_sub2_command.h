#ifndef PUREMVC_MACRO_COMMAND_TEST_SUB2_COMMAND_H
#define PUREMVC_MACRO_COMMAND_TEST_SUB2_COMMAND_H

#include "interfaces/simple_command.h"

typedef struct MacroCommandTestSub2Command MacroCommandTestSub2Command;

struct MacroCommandTestSub2Command {
    SimpleCommand super;
};

MacroCommandTestSub2Command *newMacroCommandTestSub2Command();

#endif //PUREMVC_MACRO_COMMAND_TEST_SUB2_COMMAND_H
