/*
* Header for the display command implementation
* Lab 5
*/


#pragma once
/*
 * DisplayCommand
 * --------------
 * Usage:
 *   ds <filename>        // formatted (visitor)
 *   ds <filename> -d     // raw data only
 */

#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFileSystem.h"

class DisplayCommand : public AbstractCommand {
private:
    AbstractFileSystem* fileSystem;
public:
    explicit DisplayCommand(AbstractFileSystem* fs);
    void displayInfo() override;
    int  execute(std::string args) override;
};
