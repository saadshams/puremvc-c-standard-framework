#ifndef PUREMVC_MACRO_COMMAND_H
#define PUREMVC_MACRO_COMMAND_H

#include "simple_command.h"

typedef struct SubCommand SubCommand;

struct SubCommand {
    SimpleCommand *(*commandFactory)();
    SubCommand *next;
};

typedef struct MacroCommand MacroCommand;

struct MacroCommand {
    SubCommand *SubCommands;
    void (*initializeMacroCommand)(MacroCommand *self);
    void (*addSubCommand)(MacroCommand *self, SimpleCommand *(*commandClassRef)());
    void (*execute)(MacroCommand *self, Notification *notification);
    void (*release)(MacroCommand *self);
    MacroCommand *base;
};

MacroCommand *newMacroCommand();

#endif //PUREMVC_MACRO_COMMAND_H