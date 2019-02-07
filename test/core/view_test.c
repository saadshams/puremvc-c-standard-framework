#include "view_test.h"
#include "interfaces/view.h"
#include <assert.h>
#include <stdlib.h>
#include "view_test_mediator.h"
#include <string.h>
#include "view_test_mediator4.h"

int main() {
    testGetInstance();
    testRegisterAndRetrieveMediator();
    testHasMediator();
    testRegisterAndRemoveMediator();
    testOnRegisterAndOnRemove();
    testSuccessiveRegisterAndRemoveMediator();
    return 0;
}

void testGetInstance() {
    View *view = getViewInstance(newView);
    assert(view != NULL);
    assert(view == getViewInstance(newView));
}

void testRegisterAndRetrieveMediator() {
    View *view = getViewInstance(newView);

    ViewTestMediator *viewTestMediator = newViewTestMediator(view);
    view->registerMediator(view, (Mediator *)viewTestMediator);

    Mediator *mediator = view->retrieveMediator(view, ViewTestMediator_NAME);

    assert(mediator != NULL);
    assert(mediator->getViewComponent(mediator) == view);
    assert(strcmp(mediator->getMediatorName(mediator), ViewTestMediator_NAME) == 0);

    // clean up
    view->removeMediator(view, ViewTestMediator_NAME);
    mediator->release(mediator);
}

void testHasMediator() {
    View *view = getViewInstance(newView);

    ViewTest viewTest = (ViewTest){};
    Mediator *mediator = newMediator("hasMediatorTest", &viewTest);
    view->registerMediator(view, mediator);

    assert(view->hasMediator(view, "hasMediatorTest") == true);

    view->removeMediator(view, "hasMediatorTest");
    assert(view->hasMediator(view, "hasMediatorTest") == false);
}

void testRegisterAndRemoveMediator() {
    View *view = getViewInstance(newView);

    ViewTest viewTest = (ViewTest){};
    Mediator *mediator = newMediator("testing", &viewTest);
    view->registerMediator(view, mediator);

    Mediator *removedMediator = view->removeMediator(view, "testing");

    assert(strcmp(removedMediator->getMediatorName(removedMediator), "testing") == 0);

    assert(view->retrieveMediator(view, "testing") == NULL);
}

void testOnRegisterAndOnRemove() {
    View *view = getViewInstance(newView);

    ViewTest *viewTest = malloc(sizeof(ViewTest));
    ViewTestMediator4 *mediator = newTestMediator4(viewTest);
    view->registerMediator(view, (Mediator *)mediator);

    assert(viewTest->onRegisterCalled);

    view->removeMediator(view, ViewTestMediator4_NAME);

    assert(viewTest->onRemoveCalled);

    // clean up
    free(viewTest);
    free(mediator);
}

void testSuccessiveRegisterAndRemoveMediator() {
    View *view = getViewInstance(newView);

    ViewTest *viewTest = malloc(sizeof(ViewTest));
    ViewTestMediator *viewTestMediator = newViewTestMediator(viewTest);

    view->registerMediator(view, (Mediator *)viewTestMediator);

    assert(view->retrieveMediator(view, ViewTestMediator_NAME) == (Mediator *)viewTestMediator);

    view->removeMediator(view, ViewTestMediator_NAME);

    assert(view->removeMediator(view, ViewTestMediator_NAME) == NULL);

    assert(view->removeMediator(view, ViewTestMediator_NAME) == NULL);

    ViewTestMediator *viewTestMediator2 = newViewTestMediator(viewTest);
    view->registerMediator(view, (Mediator *)viewTestMediator2);

    assert(view->retrieveMediator(view, ViewTestMediator_NAME) == (Mediator *)viewTestMediator2);

    view->removeMediator(view, ViewTestMediator_NAME);

    assert(view->retrieveMediator(view, ViewTestMediator_NAME) == NULL);

    // clean up
    viewTestMediator->super.release(&viewTestMediator->super);
    viewTestMediator2->super.release(&viewTestMediator2->super);
}