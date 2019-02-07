#ifndef PUREMVC_OBSERVER_H
#define PUREMVC_OBSERVER_H

#include "notification.h"
#include <stdbool.h>

typedef struct Observer Observer;

struct Observer {
    void *context;
    void (*notify)(Notification *notification);
    void *(*getNotifyContext)(const Observer *self);

    void (*setNotifyContext)(Observer *self, void *notifyContext);
    void (*(*getNotifyMethod)(const Observer *self))(Notification *notification);

    void (*setNotifyMethod)(Observer *self, void (*notifyMethod)(Notification *notification));
    void (*notifyObserver)(const Observer *self, Notification *notification);

    bool (*compareNotifyContext)(const Observer *self, const void *object);
    void (*release)(Observer *self);

    Observer *base;
};

Observer *newObserver(void *notify, void *context);

#endif //PUREMVC_OBSERVER_H

