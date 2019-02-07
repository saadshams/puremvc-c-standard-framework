#include "macro_command_test.h"
#include "macro_command_test_vo.h"
#include "interfaces/notification.h"
#include "macro_command_test_command.h"
#include <stdlib.h>
#include <assert.h>

int main() {
    testMacroCommandExecute();
    return 0;
}

void testMacroCommandExecute() {
    MacroCommandTestVO *vo = newMacroCommandTestVO(5);
    Notification *notification = newNotification("MacroCommandTest", vo, NULL);

    MacroCommandTestCommand *command = newMacroCommandTestCommand();
    command->super.execute(&command->super, notification);

    assert(vo->result1 == 10);
    assert(vo->result2 == 25);

    command->super.release(&command->super);
    vo->release(vo);
    notification->release(notification);
}