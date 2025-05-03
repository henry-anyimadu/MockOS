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
        CommandPrompt();
        CommandPrompt(AbstractFileSystem*, AbstractFileFactory*);
        virtual ~CommandPrompt();
        virtual void setFileSystem(AbstractFileSystem*);
        virtual void setFileFactory(AbstractFileFactory*);
        virtual int addCommand(std::string, AbstractCommand*);
        virtual int run();
    protected:
        virtual void listCommands();
        virtual std::string prompt();

    std::map<std::string, AbstractCommand*> cmdObjects;
    AbstractFileSystem* objPointer;
    AbstractFileFactory* objFactory;
};

#endif