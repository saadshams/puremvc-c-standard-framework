#ifndef PUREMVC_VIEW_TEST_H
#define PUREMVC_VIEW_TEST_H

#include <stdbool.h>

typedef struct ViewTest ViewTest;

struct ViewTest {
    char *lastNotification;
    bool onRegisterCalled;
    bool onRemoveCalled;
    int counter;
};

static const char NOTE1[] = "Notification1";
static const char NOTE2[] = "Notification2";
static const char NOTE3[] = "Notification3";
static const char NOTE4[] = "Notification4";
static const char NOTE5[] = "Notification5";
static const char NOTE6[] = "Notification6";

void testGetInstance();
void testRegisterAndRetrieveMediator();
void testHasMediator();
void testRegisterAndRemoveMediator();
void testOnRegisterAndOnRemove();
void testSuccessiveRegisterAndRemoveMediator();

#endif //PUREMVC_VIEW_TEST_H
