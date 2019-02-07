#include "interfaces/macro_command.h"
#include <stdlib.h>

static SubCommand *newSubCommandNode(SimpleCommand *(*commandFactory)()) {
    SubCommand *self = malloc(sizeof(SubCommand));
    self->commandFactory = commandFactory;
    self->next = NULL;
    return self;
}

static void initializeMacroCommand(MacroCommand *self) {

}

static void addSubCommand(MacroCommand *self, SimpleCommand *(*commandFactory)()) { // init, append
    if(self->SubCommands == NULL) { // init
        self->SubCommands = newSubCommandNode(commandFactory);
    } else { // append
        SubCommand *cursor = self->SubCommands;
        while(cursor->next != NULL)
            cursor = cursor->next;
        cursor->next = newSubCommandNode(commandFactory);
    }
}

static void execute(MacroCommand *self, Notification *notification) {
    self->initializeMacroCommand(self);
    SubCommand *cursor = self->SubCommands;
    while(cursor != NULL) {
        SimpleCommand *commandInstance = cursor->commandFactory();
        commandInstance->execute(commandInstance, notification);
        commandInstance->release(commandInstance);
        cursor = cursor->next;
    }
}

static void release(MacroCommand *self) {
    free(self);
}

MacroCommand *newMacroCommand() {
    MacroCommand *self = malloc(sizeof(MacroCommand));
    self->SubCommands = NULL;
    self->initializeMacroCommand = initializeMacroCommand;
    self->addSubCommand = addSubCommand;
    self->execute = execute;
    self->release = release;
    self->base = self;
    return self;
}