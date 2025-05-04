/*
 * Lab 5: Abstract Parsing Strategy
 * Interface for defining parsing strategies for different macrocommands
 */

#pragma once
#include <string>
#include <vector>
#include "mockos/Constants.h"

class AbstractParsingStrategy {
public:
    virtual ~AbstractParsingStrategy() = default;
    virtual std::vector<std::string> parse(const std::string& input) = NULL_DEFINITION;
};

