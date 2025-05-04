/**
 *Parsing Strategy Header for te
 *Derived from the Parsing Strategy Interface
 */



#pragma once
#include "mockos/AbstractParsingStrategy.h"
#include <sstream>
#include <vector>

class TouchEditParsingStrategy : public AbstractParsingStrategy {
public:
    std::vector<std::string> parse(const std::string& input) override {
        std::istringstream iss(input);
        std::string filename, flag;
        iss >> filename >> flag;          // flag may be ""

        if (flag == "-a")
            return { filename, filename + " -a" };  // cat in append mode
        else
            return { filename, filename };          // plain cat
    }
};
