/*
 *Created to overide the displayinfo for the created te command
 */



#include <iostream>
#include "mockos/TouchEditMacro.h"




void TouchEditMacro::displayInfo() {
    std::cout << "te <filename> [-a]\n"
                 "Creates a new file (touch) and immediately opens it\n"
                 "in the cat editor.\n"
                 "  -a   open in append mode (same flag cat accepts)\n";
}
