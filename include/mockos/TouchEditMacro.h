/**
 *TouchEdit Macro
 *Allows for the overrid of display info to display the proper help for te
 */

#ifndef TOUCHEDITMARCO_H
#define TOUCHEDITMARCO_H


#include "mockos/MacroCommand.h"

class TouchEditMacro : public MacroCommand {
public:
    void displayInfo() override;   // declaration only
};


#endif //TOUCHEDITMARCO_H
