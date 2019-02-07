#ifndef PUREMVC_MODEL_TEST_PROXY_H
#define PUREMVC_MODEL_TEST_PROXY_H

#include "interfaces/proxy.h"

#define ON_REGISTER_CALLED "onRegister Called";
#define ON_REMOVE_CALLED "onRemove Called";

typedef struct ModelTestProxy ModelTestProxy;

struct ModelTestProxy {
    Proxy super;
};

ModelTestProxy *newModelTestProxy(char*, void*);

#endif //PUREMVC_MODEL_TEST_PROXY_H
