#include "interfaces/proxy.h"
#include <string.h>

static char *getProxyName(const Proxy *self) {
    return self->proxyName;
}

static void setData(Proxy *self, void *data) {
    self->data = data;
}

static void *getData(const Proxy *self) {
    return self->data;
}

static void onRegister(Proxy *self) {

}

static void onRemove(Proxy *self) {

}

static void release(Proxy *self) {
    free(self->proxyName);
    self->data = NULL;
    free(self);
}

Proxy *newProxy(const char *proxyName, void *data) {
    Proxy *self = malloc(sizeof(Proxy));
    self->base = self;
    self->proxyName = strdup(proxyName != NULL ? proxyName : PROXY_NAME);
    self->data = data != NULL ? data : NULL;
    self->getProxyName = getProxyName;
    self->setData = setData;
    self->getData = getData;
    self->onRegister = onRegister;
    self->onRemove = onRemove;
    self->release = release;
    return self;
}