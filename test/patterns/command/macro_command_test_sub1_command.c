#include "macro_command_test_sub1_command.h"
#include "macro_command_test_vo.h"
#include <stdlib.h>

static void execute(const SimpleCommand *self, Notification *notification) {
    MacroCommandTestVO *vo = notification->getBody(notification);
    vo->result1 = 2 * vo->input;
}

static void release(SimpleCommand *self) {
    free(self);
}

MacroCommandTestSub1Command *newMacroCommandTestSub1Command() {
    MacroCommandTestSub1Command *self = malloc(sizeof(MacroCommandTestSub1Command));
    self->super.execute = execute;
    self->super.release = release;
    return self;
}