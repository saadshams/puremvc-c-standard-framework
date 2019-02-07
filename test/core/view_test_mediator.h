#ifndef PUREMVC_VIEW_TEST_MEDIATOR_H
#define PUREMVC_VIEW_TEST_MEDIATOR_H

#include "interfaces/mediator.h"

typedef struct ViewTestMediator ViewTestMediator;

struct ViewTestMediator {
    Mediator super;
};

static char ViewTestMediator_NAME[] = "ViewTestMediator";

ViewTestMediator *newViewTestMediator(void *view);

#endif //PUREMVC_VIEW_TEST_MEDIATOR_H
