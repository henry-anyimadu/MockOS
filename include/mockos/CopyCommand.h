#pragma once
/*
 * CopyCommand
 * -----------
 * Usage:
 *   cp <existing_file> <new_base_name>
 *
 * Example:
 *   cp data.txt data_copy        // produces data_copy.txt
 */

#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFileSystem.h"

class CopyCommand : public AbstractCommand {
private:
    AbstractFileSystem* fileSystem;
public:
    explicit CopyCommand(AbstractFileSystem* fs);
    void displayInfo() override;
    int  execute(std::string args) override;
};
