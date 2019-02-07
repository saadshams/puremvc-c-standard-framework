#ifndef PUREMVC_MACRO_COMMAND_TEST_COMMAND_H
#define PUREMVC_MACRO_COMMAND_TEST_COMMAND_H

#include "interfaces/notification.h"
#include "interfaces/macro_command.h"

typedef struct MacroCommandTestCommand MacroCommandTestCommand;

struct MacroCommandTestCommand {
    MacroCommand super;
};

MacroCommandTestCommand *newMacroCommandTestCommand();

#endif //PUREMVC_MACRO_COMMAND_TEST_COMMAND_H