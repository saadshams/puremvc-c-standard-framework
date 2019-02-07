#ifndef PUREMVC_MODEL_H
#define PUREMVC_MODEL_H

#include "proxy.h"
#include <stdbool.h>

typedef struct ProxyNode ProxyNode;

struct ProxyNode {
    char *name;
    Proxy *proxy;
    ProxyNode *next;
};

typedef struct Model Model;

struct Model {
    ProxyNode *proxyMap;
    void (*registerProxy)(Model *self, Proxy *proxy);
    Proxy *(*retrieveProxy)(const Model *self, const char *proxyName);
    bool (*hasProxy)(const Model *self, const char *proxyName);
    Proxy *(*removeProxy)(Model *self, const char *proxyName);
    void (*release)(Model *self);
    Model *base;
};

Model *newModel();
Model *getModelInstance(Model *(modelFactory)());

#endif //PUREMVC_MODEL_H
