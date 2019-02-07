#include "model_test_proxy.h"
#include <stdlib.h>

static void onRegister(Proxy *self) {
    self->data = (void *)ON_REGISTER_CALLED;
}

static void onRemove(Proxy *self) {
    self->data = (void *)ON_REMOVE_CALLED;
}

ModelTestProxy *newModelTestProxy(char *proxyName, void *data) {
    ModelTestProxy *self = malloc(sizeof(ModelTestProxy));
    self->super = *newProxy(proxyName, data);
    self->super.onRegister = onRegister;
    self->super.onRemove = onRemove;
    return self;
}
