#ifndef PUREMVC_SIMPLE_COMMAND_TEST_VO_H
#define PUREMVC_SIMPLE_COMMAND_TEST_VO_H

typedef struct SimpleCommandTestVO SimpleCommandTestVO;

struct SimpleCommandTestVO {
    int input;
    int result;
    void (*release)(SimpleCommandTestVO *self);
};

SimpleCommandTestVO *newSimpleCommandTestVO(int input);

#endif //PUREMVC_SIMPLE_COMMAND_TEST_VO_H
