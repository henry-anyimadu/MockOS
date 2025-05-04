/*
 * Studio 21: Abstract Command Header File
 */
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