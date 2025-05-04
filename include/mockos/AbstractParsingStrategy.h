#pragma once
#include <string>
#include <vector>

class AbstractParsingStrategy {
public:
    virtual ~AbstractParsingStrategy() = default;
    virtual std::vector<std::string> parse(const std::string& input) = 0;
};

