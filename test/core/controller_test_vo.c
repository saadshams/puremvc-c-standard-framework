#include "controller_test_vo.h"
#include <stdlib.h>

static void release(ControllerTestVO *self) {
    free(self);
}

ControllerTestVO *newControllerTestVO(int input) {
    ControllerTestVO *self = malloc(sizeof(ControllerTestVO));
    self->input = input;
    self->result = 0;
    self->release = release;
    return self;
}