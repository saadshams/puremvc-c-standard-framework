#include "observer_test.h"
#include "interfaces/observer.h"
#include <stdlib.h>
#include <assert.h>

int main() {
    testObserverAccessors();
    testObserverConstructor();
    testCompareNotifyContext();
    return 0;
}

int observerTestVar;
static void *this = (void *)4;

void testObserverAccessors() {
    Observer *observer = newObserver(NULL, NULL);

    observer->setNotifyMethod(observer, (const void *)observerTestMethod);
    observer->setNotifyContext(observer, this);

    Notification *notification = newNotification("ObserverTestNote", (void *)10, NULL);
    observer->notifyObserver(observer, notification);

    assert(observerTestVar == 10);

    notification->release(notification);
    observer->release(observer);
}

void testObserverConstructor() {
    Observer *observer = newObserver(observerTestMethod, observer);
    Notification *notification = newNotification("ObserverTestNote", (void *)5, NULL);
    observer->notifyObserver(observer, notification);

    assert(observerTestVar == 5);

    notification->release(notification);
    observer->release(observer);
}

void testCompareNotifyContext() {
    Observer *observer = newObserver(observerTestMethod, this);

    void *negTestObj = (void *)8;
    assert(observer->compareNotifyContext(observer, negTestObj) == false);
    assert(observer->compareNotifyContext(observer, this) == true);

    observer->release(observer);
}

static void observerTestMethod(Notification *notification) {
    observerTestVar = (int)notification->getBody(notification);
}