#include "simple_command_test.h"
#include "simple_command_test_vo.h"
#include "interfaces/notification.h"
#include "simple_command_test_command.h"
#include <stdlib.h>
#include <assert.h>

int main() {
    testSimpleCommandExecute();
    return 0;
}

void testSimpleCommandExecute() {
    SimpleCommandTestVO *vo = newSimpleCommandTestVO(5);
    Notification *note = newNotification("SimpleCommandTestNote", vo, NULL);

    SimpleCommandTestCommand *command = newSimpleCommandTestCommand();
    command->super.execute(&command->super, note);

    assert(vo->result == 10);

    vo->release(vo);
    note->release(note);
    command->super.release(&command->super);
}