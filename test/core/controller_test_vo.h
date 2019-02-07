#ifndef PUREMVC_CONTROLLER_TEST_VO_H
#define PUREMVC_CONTROLLER_TEST_VO_H

typedef struct ControllerTestVO ControllerTestVO;

struct ControllerTestVO {
    int input;
    int result;
    void (*release)(ControllerTestVO *self);
};

ControllerTestVO *newControllerTestVO(int input);

#endif //PUREMVC_CONTROLLER_TEST_VO_H
