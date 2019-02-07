#ifndef PUREMVC_PROXY_H
#define PUREMVC_PROXY_H

#include <stdlib.h>

typedef struct Proxy Proxy;

struct Proxy {
    char *proxyName;
    void *data;
    char *(*getProxyName)(const Proxy *self);
    void (*setData)(Proxy *self, void *data);
    void *(*getData)(const Proxy *self);
    void (*onRegister)(Proxy *self);
    void (*onRemove)(Proxy *self);
    void (*release)(Proxy *self);
    Proxy *base;
};

static char *PROXY_NAME = "Proxy";

Proxy *newProxy(const char *proxyName, void *data);

#endif //PUREMVC_PROXY_H