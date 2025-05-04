/*
 * Derived from the AbstractParsingStrategy
 * Implementation for the parsing strategy for rn
 * cp + rm
 */


#pragma once
#include "mockos/AbstractParsingStrategy.h"
#include <vector>
#include <string>
#include <sstream>

class RenameParsingStrategy : public AbstractParsingStrategy {
public:
    std::vector<std::string> parse(const std::string& input) override {
        std::istringstream iss(input);
        std::string oldName, newBase;
        iss >> oldName >> newBase;
        return { oldName + " " + newBase,   // for cp
                 oldName };                 // for rm
    }

};