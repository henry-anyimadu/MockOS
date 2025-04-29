/*
 * Studio 21: Abstract Command Header File
 */
#pragma once
#include <string>

class AbstractCommand {
    public:
    AbstractCommand();
    virtual ~AbstractCommand() = default;
    virtual int execute(std::string info) = 0; // Holds info that is passed to the command
    virtual void displayInfo() = 0; // Usage message for the command
};