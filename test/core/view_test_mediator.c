#include "view_test_mediator.h"
#include <stdlib.h>

static char **listNotificationInterests(const Mediator *self) {
    return (char *[]){"ABC", "DEF", "GHI"};
}

ViewTestMediator *newViewTestMediator(void *view) {
    ViewTestMediator *self = malloc(sizeof(ViewTestMediator));
    self->super = *newMediator(ViewTestMediator_NAME, view);
    self->super.listNotificationInterests = listNotificationInterests;
    return self;
}