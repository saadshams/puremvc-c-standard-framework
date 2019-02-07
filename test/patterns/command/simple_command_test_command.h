#ifndef PUREMVC_SIMPLECOMMANDTESTCOMMAND_H
#define PUREMVC_SIMPLECOMMANDTESTCOMMAND_H

#include "interfaces/simple_command.h"
#include "interfaces/notification.h"

typedef struct SimpleCommandTestCommand SimpleCommandTestCommand;

struct SimpleCommandTestCommand {
    SimpleCommand super;
};

SimpleCommandTestCommand *newSimpleCommandTestCommand();

#endif //PUREMVC_SIMPLECOMMANDTESTCOMMAND_H
