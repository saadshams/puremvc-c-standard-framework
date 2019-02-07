#ifndef PUREMVC_VIEW_H
#define PUREMVC_VIEW_H

#include "mediator.h"
#include <stdbool.h>

typedef struct MediatorNode MediatorNode;

struct MediatorNode {
    char *name;
    Mediator *mediator;
    MediatorNode *next;
};

typedef struct View View;

struct View {
    MediatorNode *mediatorMap;
    void (*registerMediator)(View *self, Mediator *mediator);
    Mediator *(*retrieveMediator)(View *self, const char *mediatorName);
    bool (*hasMediator)(View *self, const char *mediatorName);
    Mediator *(*removeMediator)(View *self, const char *mediatorName);
    void (*release)(View *self);
    View *base;
};

View *newView();

View *getViewInstance(View *(viewFactory)());

#endif //PUREMVC_VIEW_H
