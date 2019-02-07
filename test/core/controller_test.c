#include "controller_test.h"
#include "interfaces/controller.h"
#include <stdlib.h>
#include <assert.h>
#include "controller_test_command.h"
#include "controller_test_command2.h"
#include "controller_test_vo.h"
#include <assert.h>
#include <stdio.h>

int main() {
    testGetInstance();
    testRegisterAndExecuteCommand();
    testRegisterAndRemoveCommand();
    testHasCommand();
    testReregisterAndExecuteCommand();
    return 0;
}

void testGetInstance() {
    Controller *controller = getControllerInstance(newController);
    assert(controller != NULL);
    assert(controller == getControllerInstance(newController));
}

void testRegisterAndExecuteCommand() {
    Controller *controller = getControllerInstance(&newController);
    controller->registerCommand(controller, "ControllerTest", (SimpleCommand *(*)())newControllerTestCommand);
    ControllerTestVO *vo = newControllerTestVO(12);
    Notification *notification = newNotification("ControllerTest", vo, NULL);
    controller->executeCommand(controller, notification);
    assert(vo->result == 24);
}

void testRegisterAndRemoveCommand() {
    Controller *controller = getControllerInstance(newController);
    controller->registerCommand(controller, "ControllerRemoveTest", (SimpleCommand *(*)())newControllerTestCommand);
    ControllerTestVO *vo = newControllerTestVO(12);
    Notification *notification = newNotification("ControllerRemoveTest", vo, NULL);
    controller->executeCommand(controller, notification);
    assert(vo->result == 24);

    vo->result = 0;
    controller->removeCommand(controller, "ControllerRemoveTest");

    controller->executeCommand(controller, notification);

    assert(vo->result == 0);
}

void testHasCommand() {
    Controller *controller = getControllerInstance(newController);

    controller->registerCommand(controller, "hasCommandTest", (SimpleCommand *(*)())newControllerTestCommand);
    assert(controller->hasCommand(controller, "hasCommandTest"));

    controller->registerCommand(controller, "hasCommandTest2", (SimpleCommand *(*)())newControllerTestCommand2);
    assert(controller->hasCommand(controller, "hasCommandTest2"));

    controller->removeCommand(controller, "hasCommandTest2");
    assert(controller->hasCommand(controller, "hasCommandTest2") == false);

    controller->removeCommand(controller, "hasCommandTest");
    assert(controller->hasCommand(controller, "hasCommandTest") == false);
}

void testReregisterAndExecuteCommand() {
    Controller *controller = getControllerInstance(newController);
    controller->registerCommand(controller, "ControllerTest2", (SimpleCommand *(*)())newControllerTestCommand);
    controller->registerCommand(controller, "ControllerTest2", (SimpleCommand *(*)())newControllerTestCommand2);
    ControllerTestVO *vo = newControllerTestVO(12);
    Notification *notification = newNotification("ControllerTest2", vo, NULL);
    controller->executeCommand(controller, notification);
    assert(vo->result == 24);
    controller->removeCommand(controller, "ControllerTst2");
    notification->release(notification);
    vo->release(vo);

    controller->registerCommand(controller, "ControllerTest2", (SimpleCommand *(*)())newControllerTestCommand);
    controller->removeCommand(controller, "ControllerTest2");
    controller->registerCommand(controller, "ControllerTest2", (SimpleCommand *(*)())newControllerTestCommand2);

    vo = newControllerTestVO(12);
    notification = newNotification("ControllerTest2", vo, NULL);


    // view tests

    vo->release(vo);
    notification->release(notification);

}