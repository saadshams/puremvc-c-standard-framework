#include "view_test_mediator4.h"
#include <stdlib.h>

void onRegister(Mediator *self) {
    ViewTest *viewTest = (ViewTest *)self->getViewComponent(self);
    viewTest->onRegisterCalled = true;
}

void onRemove(Mediator *self) {
    ViewTest *viewTest = (ViewTest *)self->getViewComponent(self);
    viewTest->onRemoveCalled = true;
}

ViewTestMediator4 *newTestMediator4(ViewTest *view) {
    ViewTestMediator4 *self = malloc(sizeof(ViewTestMediator4));
    self->super = *newMediator(ViewTestMediator4_NAME, view);
    self->super.onRegister = onRegister;
    self->super.onRemove = onRemove;
    return self;
}