/*
 *Macro Command Header
 *Derived from the abstract command interface
 *Part of Lab 5
 */


#pragma once
#include "mockos/AbstractCommand.h"
#include "mockos/AbstractParsingStrategy.h"
#include <vector>
#include "AbstractFileSystem.h"

class MacroCommand : public AbstractCommand {
private:
    std::vector<AbstractCommand*> commands;
    AbstractParsingStrategy*      strategy = nullptr;
    AbstractFileSystem* fs = nullptr;
public:
    MacroCommand() = default;
    explicit MacroCommand(AbstractFileSystem* p) : fs(p) {}
    //overload for 2 pointers

    void addCommand(AbstractCommand* cmd);
    void setParseStrategy(AbstractParsingStrategy* strat);

    // AbstractCommand interface
    void displayInfo() override;
    int  execute(std::string input) override;
};
