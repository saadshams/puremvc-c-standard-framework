#ifndef PUREMVC_MACRO_COMMAND_TEST_VO_H
#define PUREMVC_MACRO_COMMAND_TEST_VO_H

typedef struct MacroCommandTestVO MacroCommandTestVO;

struct MacroCommandTestVO {
    int input;
    int result1;
    int result2;
    void (*release)(MacroCommandTestVO *self);
};

MacroCommandTestVO *newMacroCommandTestVO(int input);

#endif //PUREMVC_MACRO_COMMAND_TEST_VO_H
