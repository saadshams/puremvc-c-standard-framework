#include "notification_test.h"
#include "interfaces/notification.h"
#include <assert.h>
#include <string.h>

int main() {
    testNameAccessors();
    testBodyAccessors();
    testConstructor();
    return 0;
}

void testNameAccessors() {
    Notification *notification = newNotification("TestNote", NULL, NULL);
    assert(strcmp(notification->getName(notification), "TestNote") == 0);
    notification->release(notification);
}

void testBodyAccessors() {
    Notification *notification = newNotification(NULL, NULL, NULL);
    notification->setBody(notification, (void*)5);
    assert((int)notification->getBody(notification) == 5);
    notification->release(notification);
}

void testConstructor() {
    Notification *notification = newNotification("TestNote", (void *)5, "TestNoteType");
    assert(strcmp(notification->getName(notification), "TestNote") == 0);
    assert((int)notification->getBody(notification) == 5);
    assert(strcmp(notification->getType(notification), "TestNoteType") == 0);
    notification->release(notification);
}