/*
 *Header file for creating an overrwitten displayInfo() message for the
 *rn command
 */



#ifndef RENAMEMACRO_H
#define RENAMEMACRO_H

#include "mockos/MacroCommand.h"

// A macro command that renames a file: cp + rm
class RenameMacro : public MacroCommand {
public:
    void displayInfo() override;   // declaration only
};

#endif // RENAMEMACRO_H
