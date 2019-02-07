#include "interfaces/model.h"
#include <pthread.h>
#include <string.h>
#include <assert.h>

static Model *instance;
pthread_mutex_t model_mutex = PTHREAD_MUTEX_INITIALIZER;

static ProxyNode *newProxyNode(Proxy *proxy) {
    ProxyNode *self = malloc(sizeof(ProxyNode));
    self->name = strdup(proxy->getProxyName(proxy));
    self->proxy = proxy;
    self->next = NULL;
    return self;
}

static void registerProxy(Model *self, Proxy *proxy) { // init, update, append
    if(self->proxyMap == NULL) { // base case, initialize
        self->proxyMap = newProxyNode(proxy);
    } else {
        ProxyNode *cursor = self->proxyMap;
        if(self->hasProxy(self, proxy->getProxyName(proxy))) { // update existing proxy
            while(cursor != NULL && strcmp(cursor->name, proxy->getProxyName(proxy)) != 0)
                cursor = cursor->next;
            cursor->proxy->release(cursor->proxy);
            cursor->proxy = proxy;
        } else { // append
            while(cursor->next != NULL)
                cursor = cursor->next;
            cursor->next = newProxyNode(proxy);
        }
    }
    proxy->onRegister(proxy);
}

static Proxy *retrieveProxy(const Model *self, const char *proxyName) {
    ProxyNode *cursor = self->proxyMap;
    while (cursor != NULL && strcmp(cursor->name, proxyName) != 0)
        cursor = cursor->next;
    return cursor == NULL ? NULL : cursor->proxy;
}

static bool hasProxy(const Model *self, const char *proxyName) {
    ProxyNode *cursor = self->proxyMap;
    while (cursor != NULL && strcmp(cursor->name, proxyName) != 0)
        cursor = cursor->next;
    return cursor != NULL;
}

static Proxy *removeProxy(Model *self, const char *proxyName) {
    if(self->proxyMap == NULL) return NULL;

    Proxy *proxy = NULL;
    if(strcmp(self->proxyMap->name, proxyName) == 0) { // base case if the node is the first node
        ProxyNode *temp = self->proxyMap;
        self->proxyMap = temp->next;
        proxy = temp->proxy;
        proxy->release(proxy);
    } else {
        ProxyNode *cursor = self->proxyMap;
        while (cursor->next != NULL && strcmp(cursor->next->name, proxyName) != 0) // search
            cursor = cursor->next;

        if(cursor->next != NULL) {
            ProxyNode *temp = cursor->next;
            proxy = temp->proxy;
            cursor->next = temp->next;
            proxy->release(proxy);
        }
    }

    if(proxy != NULL) proxy->onRemove(proxy);
    return proxy;
}

static void release(Model *self) {
    free(self);
}

Model *newModel() {
    assert(instance == NULL);
    Model *self = malloc(sizeof(Model));
    self->base = self;
    self->proxyMap = NULL;
    self->registerProxy = registerProxy;
    self->retrieveProxy = retrieveProxy;
    self->hasProxy = hasProxy;
    self->removeProxy = removeProxy;
    self->release = release;
    instance = self;
    return self;
}

Model *getModelInstance(Model *(modelFactory)()) {
    pthread_mutex_lock(&model_mutex);
    if(instance == NULL) {
        instance = modelFactory();
    }
    pthread_mutex_unlock(&model_mutex);
    return instance;
}