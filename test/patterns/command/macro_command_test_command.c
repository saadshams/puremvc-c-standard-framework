#include "macro_command_test_command.h"
#include "macro_command_test_sub1_command.h"
#include "macro_command_test_sub2_command.h"
#include <stdlib.h>

static void initializeMacroCommand(MacroCommand *self) {
    self->addSubCommand(self, (SimpleCommand *(*)())newMacroCommandTestSub1Command);
    self->addSubCommand(self, (SimpleCommand *(*)())newMacroCommandTestSub2Command);
}

MacroCommandTestCommand *newMacroCommandTestCommand() {
    MacroCommandTestCommand *self = malloc(sizeof(MacroCommandTestCommand));
    self->super = *newMacroCommand();
    self->super.initializeMacroCommand = initializeMacroCommand;
    return self;
}
