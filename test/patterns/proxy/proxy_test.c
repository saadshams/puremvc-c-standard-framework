#include "interfaces/proxy.h"
#include "proxy_test.h"
#include <assert.h>
#include <string.h>

int main() {
    testNameAccessor();
    testDataAccessors();
    testConstructor();
    return 0;
}

typedef struct StringArray StringArray;
struct StringArray {
    int length;
    char **values;
};

void testNameAccessor() {
    Proxy *proxy = newProxy("TestProxy", NULL);
    assert(proxy != NULL);
    assert(strcmp(proxy->getProxyName(proxy), "TestProxy") == 0);
    proxy->release(proxy);
}

void testDataAccessors() {
    Proxy *proxy = newProxy("colors", NULL);
    assert(proxy != NULL);
    proxy->setData(proxy, &(StringArray){3, (char *[]){"red", "green", "blue"}});

    StringArray *data = proxy->getData(proxy);
    assert(data->length == 3);
    assert(data->values[0] == "red");
    assert(data->values[1] == "green");
    assert(data->values[2] == "blue");

    proxy->release(proxy);
}

void testConstructor() {
    Proxy *proxy = newProxy("colors", &(StringArray) {3, (char *[]) {"red", "green", "blue"}});
    StringArray *data = proxy->getData(proxy);

    assert(proxy != NULL);
    assert(strcmp(proxy->getProxyName(proxy), "colors") == 0);

    assert(data->length == 3);
    assert(data->values[0] == "red");
    assert(data->values[1] == "green");
    assert(data->values[2] == "blue");

    proxy->release(proxy);
}
