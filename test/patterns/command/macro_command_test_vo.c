#include "macro_command_test_vo.h"
#include <stdlib.h>

static void release(MacroCommandTestVO *self) {
    free(self);
}

MacroCommandTestVO *newMacroCommandTestVO(int input) {
    MacroCommandTestVO *macroCommandTestVO = malloc(sizeof(MacroCommandTestVO));
    macroCommandTestVO->input = input;
    macroCommandTestVO->release = release;
    return macroCommandTestVO;
}
