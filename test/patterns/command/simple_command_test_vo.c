#include "simple_command_test_vo.h"
#include <stdlib.h>

void release(SimpleCommandTestVO *self) {
    free(self);
}

SimpleCommandTestVO *newSimpleCommandTestVO(int input) {
    SimpleCommandTestVO *simpleCommandTestVO = malloc(sizeof(SimpleCommandTestVO));
    simpleCommandTestVO->input = input;
    simpleCommandTestVO->release = release;
    return simpleCommandTestVO;
}