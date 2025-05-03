#pragma once
/*
 * CatCommand
 * Usage:  cat <filename> [-a]
 *   -a : append mode (show file, then append)
 *        no flag = overwrite mode (do not show file, replace contents)
 */

#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFileSystem.h"

class CatCommand : public AbstractCommand {
private:
    AbstractFileSystem* fileSystem;
public:
    explicit CatCommand(AbstractFileSystem* fs);
    void displayInfo() override;
    int  execute(std::string args) override;
};
