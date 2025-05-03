/*
* Lab 5: RemoveCommand header
*/
#pragma once

#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFileSystem.h"
#include <string>

class RemoveCommand : public AbstractCommand {
    private:
    AbstractFileSystem* fileSystem;

    public:
    explicit RemoveCommand(AbstractFileSystem* fileSystem);
    ~RemoveCommand() = default;
    void displayInfo() override;
    int execute(std::string file) override;
};