#ifndef PUREMVC_NOTIFICATION_H
#define PUREMVC_NOTIFICATION_H

typedef struct Notification Notification;

struct Notification {
    char *name;
    void *body;
    char *type;
    char *(*getName)(const Notification *self);
    void (*setBody)(Notification *self, void *body);
    void *(*getBody)(const Notification *self);
    void (*setType)(Notification *self, const char *type);
    char *(*getType)(const Notification *self);
    void (*release)(Notification *self);
    Notification *base;
};

Notification *newNotification(char *name, void *body, char *type);

#endif //PUREMVC_NOTIFICATION_H