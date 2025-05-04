//
// Created by Jonah Sachs on 5/3/25.
//

#include <iostream>
#include "mockos/RenameMacro.h"


void RenameMacro::displayInfo() {
    std::cout << "rn <existing_file> <new_base>\n"
                 "Renames a file by copying it to <new_base>.<ext>\n"
                 "and then deleting the original.\n";
}

