/*
 * Studio 21: TouchCommand Header File
 * For the touch command for creating files
 */
#ifndef MOCKOS_TOUCH_COMMAND_H
#define MOCKOS_TOUCH_COMMAND_H
#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFileSystem.h"
#include "mockos/AbstractFileFactory.h"

class TouchCommand : public AbstractCommand {
private:
    AbstractFileSystem* fileSystem;
    AbstractFileFactory* fileFactory;

public:
    TouchCommand(AbstractFileSystem* fileSys, AbstractFileFactory* fileFact);
    ~TouchCommand() = default;

    void displayInfo() override;
    int execute(std::string filename) override;
};
#endif