/*
 * Studio 21: CommandPrompt header file
 */

#ifndef MOCKOS_COMMANDPROMPT_H
#define MOCKOS_COMMANDPROMPT_H

#include <map>
#include <string>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

class CommandPrompt {
    public:
        CommandPrompt(AbstractFileSystem*, AbstractFileFactory*);
        virtual ~CommandPrompt() = 0;
        virtual void setFileSystem(AbstractFileSystem*);
        virtual void setFileFactory(AbstractFileFactory*);
        virtual int addCommand(std::string, AbstractCommand*);
    protected:
        int listCommands();
        std::string prompt();
        int run();

    std::map<std::string, AbstractCommand*> cmdObjects;
    AbstractFileSystem* objPointer;
    AbstractFileFactory* objFactory;
};

#endif