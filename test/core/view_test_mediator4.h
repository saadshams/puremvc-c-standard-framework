#ifndef PUREMVC_VIEW_TEST_MEDIATOR4_H
#define PUREMVC_VIEW_TEST_MEDIATOR4_H

#include "interfaces/mediator.h"
#include "view_test.h"

typedef struct ViewTestMediator4 ViewTestMediator4;

struct ViewTestMediator4 {
    Mediator super;
};

static char ViewTestMediator4_NAME[] = "ViewTestMediator4";

ViewTestMediator4 *newTestMediator4(ViewTest *view);


#endif //PUREMVC_VIEW_TEST_MEDIATOR4_H
