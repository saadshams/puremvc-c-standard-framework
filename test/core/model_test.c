#include "model_test.h"
#include "interfaces/model.h"
#include "model_test_proxy.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef struct StringArray StringArray;
struct StringArray {
    int length;
    char **values;
};

int main() {
    testGetInstance();
    testRegisterAndRetrieveProxy();
    testRegisterAndRemoveProxy();
    testReRegisterAndRetrieveProxy();
    testHasProxy();
    testOnRegisterAndOnRemove();
    return 0;
}

void testGetInstance() {
    Model *model = getModelInstance(newModel);
    assert(model != NULL);
    assert(model == getModelInstance(newModel));
}

void testRegisterAndRetrieveProxy() {
    Model *model = getModelInstance(newModel);
    model->registerProxy(model, newProxy("colors", &(StringArray){3, (char *[]){"red", "green", "blue"}}));
    Proxy *proxy = model->retrieveProxy(model, "colors");

    assert(proxy != NULL);
    StringArray *data = proxy->getData(proxy);
    assert(data->length == 3);
    assert(strcmp(data->values[0], "red") == 0);
    assert(strcmp(data->values[1], "green") == 0);
    assert(strcmp(data->values[2], "blue") == 0);

    assert(strcmp(model->removeProxy(model, "colors")->proxyName, "colors") == 0);
    assert(model->retrieveProxy(model, "colors") == NULL);
}

void testRegisterAndRemoveProxy() {
    Model *model = getModelInstance(newModel);
    model->registerProxy(model, newProxy("colors", &(StringArray){3, (char *[]){"red", "green", "blue"}}));
    model->registerProxy(model, newProxy("aces", &(StringArray){4, (char *[]){"clubs", "spades", "hearts", "diamonds"}}));
    model->registerProxy(model, newProxy("stooges", &(StringArray){3, (char *[]){"moe", "larry", "curly"}}));
    model->registerProxy(model, newProxy("sizes", &(StringArray){3, (char *[]){"7", "13", "21"}}));

    // removal order FIFO
    assert(strcmp(model->removeProxy(model, "colors")->proxyName, "colors") == 0);
    assert(strcmp(model->removeProxy(model, "aces")->proxyName, "aces") == 0);
    assert(strcmp(model->removeProxy(model, "stooges")->proxyName, "stooges") == 0);
    assert(strcmp(model->removeProxy(model, "sizes")->proxyName, "sizes") == 0);

    assert(model->retrieveProxy(model, "colors") == NULL);
    assert(model->retrieveProxy(model, "aces") == NULL);
    assert(model->retrieveProxy(model, "stooges") == NULL);
    assert(model->retrieveProxy(model, "sizes") == NULL);

    // change removal order - random
    model->registerProxy(model, newProxy("colors", &(StringArray){3, (char *[]){"red", "green", "blue"}}));
    model->registerProxy(model, newProxy("aces", &(StringArray){4, (char *[]){"clubs", "spades", "hearts", "diamonds"}}));
    model->registerProxy(model, newProxy("stooges", &(StringArray){3, (char *[]){"moe", "larry", "curly"}}));
    model->registerProxy(model, newProxy("sizes", &(StringArray){3, (char *[]){"7", "13", "21"}}));

    assert(strcmp(model->removeProxy(model, "stooges")->proxyName, "stooges") == 0);
    assert(strcmp(model->removeProxy(model, "aces")->proxyName, "aces") == 0);
    assert(strcmp(model->removeProxy(model, "sizes")->proxyName, "sizes") == 0);
    assert(strcmp(model->removeProxy(model, "colors")->proxyName, "colors") == 0);

    assert(model->retrieveProxy(model, "colors") == NULL);
    assert(model->retrieveProxy(model, "aces") == NULL);
    assert(model->retrieveProxy(model, "stooges") == NULL);
    assert(model->retrieveProxy(model, "sizes") == NULL);

    // change removal order - LIFO
    model->registerProxy(model, newProxy("colors", &(StringArray){3, (char *[]){"red", "green", "blue"}}));
    model->registerProxy(model, newProxy("aces", &(StringArray){4, (char *[]){"clubs", "spades", "hearts", "diamonds"}}));
    model->registerProxy(model, newProxy("stooges", &(StringArray){3, (char *[]){"moe", "larry", "curly"}}));
    model->registerProxy(model, newProxy("sizes", &(StringArray){3, (char *[]){"7", "13", "21"}}));

    assert(model->removeProxy(model, "unknown") == NULL);
    assert(strcmp(model->removeProxy(model, "stooges")->proxyName, "stooges") == 0);
    assert(strcmp(model->removeProxy(model, "colors")->proxyName, "colors") == 0);
    assert(strcmp(model->removeProxy(model, "aces")->proxyName, "aces") == 0);
    assert(strcmp(model->removeProxy(model, "sizes")->proxyName, "sizes") == 0);
    assert(model->removeProxy(model, "unknown") == NULL);

    assert(model->retrieveProxy(model, "unknown") == NULL);
    assert(model->retrieveProxy(model, "colors") == NULL);
    assert(model->retrieveProxy(model, "aces") == NULL);
    assert(model->retrieveProxy(model, "stooges") == NULL);
    assert(model->retrieveProxy(model, "sizes") == NULL);
    assert(model->retrieveProxy(model, "unknown") == NULL);
}

void testReRegisterAndRetrieveProxy() {
    Model *model = getModelInstance(newModel);
    model->registerProxy(model, newProxy("colors", &(StringArray){3, (char *[]){"red", "green", "blue"}}));
    model->registerProxy(model, newProxy("colors", &(StringArray){2, (char *[]){"yellow", "orange"}})); // re-register
    Proxy *proxy = model->retrieveProxy(model, "colors");

    assert(proxy != NULL);
    StringArray *data = proxy->getData(proxy);
    assert(data != NULL);
    assert(data->length == 2);
    assert(data->values[0] == "yellow");
    assert(data->values[1] == "orange");

    assert(strcmp(model->removeProxy(model, "colors")->proxyName, "colors") == 0);
    assert(model->retrieveProxy(model, "colors") == NULL);
}

void testHasProxy() {
    Model *model = getModelInstance(newModel);
    model->registerProxy(model, newProxy("aces", &(StringArray){4, (char *[]){"clubs", "spades", "hearts", "diamonds"}}));
    assert(model->hasProxy(model, "aces") == true);
    Proxy *proxy = model->removeProxy(model, "aces");

    assert(proxy != NULL);
    proxy->release(proxy);

    assert(model->hasProxy(model, "aces") == false);

    model->registerProxy(model, newProxy("colors", &(StringArray){3, (char *[]){"red", "green", "blue"}}));
    model->registerProxy(model, newProxy("aces", &(StringArray){4, (char *[]){"clubs", "spades", "hearts", "diamonds"}}));
    model->registerProxy(model, newProxy("stooges", &(StringArray){3, (char *[]){"moe", "larry", "curly"}}));
    model->registerProxy(model, newProxy("sizes", &(StringArray){3, (char *[]){"7", "13", "21"}}));

    assert(model->hasProxy(model, "stooges") == true);
    assert(model->hasProxy(model, "aces") == true);
    assert(model->hasProxy(model, "colors") == true);
    assert(model->hasProxy(model, "sizes") == true);

    assert(strcmp(model->removeProxy(model, "stooges")->proxyName, "stooges") == 0);
    assert(strcmp(model->removeProxy(model, "colors")->proxyName, "colors") == 0);
    assert(strcmp(model->removeProxy(model, "aces")->proxyName, "aces") == 0);
    assert(strcmp(model->removeProxy(model, "sizes")->proxyName, "sizes") == 0);

    assert(model->retrieveProxy(model, "colors") == NULL);
    assert(model->retrieveProxy(model, "aces") == NULL);
    assert(model->retrieveProxy(model, "stooges") == NULL);
    assert(model->retrieveProxy(model, "sizes") == NULL);
}

void testOnRegisterAndOnRemove() {
    Model *model = getModelInstance(newModel);

    ModelTestProxy *modelTestProxy = newModelTestProxy("ModelTestProxy", NULL);
    model->registerProxy(model, (Proxy *)modelTestProxy);

    char *data = ON_REGISTER_CALLED;
    assert(strcmp(modelTestProxy->super.getData(&modelTestProxy->super), data) == 0);

    model->removeProxy(model, "ModelTestProxy");

    data = ON_REMOVE_CALLED;
    assert(modelTestProxy->super.data == data);
}