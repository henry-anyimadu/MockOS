#pragma once
#include "mockos/AbstractCommand.h"
#include "mockos/AbstractParsingStrategy.h"
#include <vector>

class MacroCommand : public AbstractCommand {
private:
    std::vector<AbstractCommand*> commands;
    AbstractParsingStrategy*      strategy = nullptr;
public:
    explicit MacroCommand() = default;

    void addCommand(AbstractCommand* cmd);
    void setParseStrategy(AbstractParsingStrategy* strat);

    // AbstractCommand interface
    void displayInfo() override;
    int  execute(std::string input) override;
};