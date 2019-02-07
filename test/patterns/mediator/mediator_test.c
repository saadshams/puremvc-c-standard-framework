#include "mediator_test.h"
#include "interfaces/mediator.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main() {
    testNameAccessor();
    testViewAccessor();
    return 0;
}

void testNameAccessor() {
    Mediator *mediator = newMediator(NULL, NULL);
    assert(strcmp(mediator->getMediatorName(mediator), MEDIATOR_NAME) == 0);
    mediator->release(mediator);
}

void testViewAccessor() {
    struct Object {} *object;
    Mediator *mediator = newMediator(MEDIATOR_NAME, object);
    void *temp = mediator->getViewComponent(mediator);

    assert(mediator->getViewComponent(mediator) == object);

    mediator->release(mediator);
}