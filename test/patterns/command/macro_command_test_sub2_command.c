#include "macro_command_test_sub2_command.h"
#include "macro_command_test_vo.h"
#include <stdlib.h>

static void execute(const SimpleCommand *self, Notification *notification) {
    MacroCommandTestVO *vo = notification->getBody(notification);
    vo->result2 = vo->input * vo->input;
}

static void release(SimpleCommand *self) {
    free(self);
}

MacroCommandTestSub2Command *newMacroCommandTestSub2Command() {
    MacroCommandTestSub2Command *self = malloc(sizeof(MacroCommandTestSub2Command));
    self->super.execute = execute;
    self->super.release = release;
    return self;
}