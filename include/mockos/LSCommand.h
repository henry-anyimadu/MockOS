/*
* Studio 21: LSCommand header
*
* “ls” prints the names of every file currently in the file system.
*/
#ifndef MOCKOS_LS_COMMAND_H
#define MOCKOS_LS_COMMAND_H

#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFileSystem.h"

class LSCommand : public AbstractCommand {
private:
 AbstractFileSystem* fileSystem;     // we only need the file‑system ptr

public:
 explicit LSCommand(AbstractFileSystem* fs); // ctor
 ~LSCommand() = default;                      // nothing to clean up

 // overrides from AbstractCommand
 void displayInfo() override;                 // prints help text
 int  execute(std::string args) override;     // runs the ls command
};

#endif // MOCKOS_LS_COMMAND_H
