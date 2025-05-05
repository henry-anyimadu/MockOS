/*
 * Studio 21: Abstract Command Header File
 */

// Author: Kelenna, Henry, Jonah
// Declaration of the AbstractCommand interface (Command pattern)
// Defines the contract for command objects (`execute`, `displayInfo`)
// Allows requests to be encapsulated as objects
#pragma once
#include <string>
#include "mockos/Constants.h"

class AbstractCommand {
    public:
    AbstractCommand();
    virtual ~AbstractCommand() = default;
    virtual int execute(std::string info) = NULL_DEFINITION; // Holds info that is passed to the command
    virtual void displayInfo() = NULL_DEFINITION; // Usage message for the command
};