/**
 *Macro Command cpp file for implementing the creation of macrocommands like rn, te
 */



#include "mockos/MacroCommand.h"
#include "mockos/Constants.h"
#include <iostream>

#include "mockos/AbstractFile.h"

void MacroCommand::addCommand(AbstractCommand* cmd) {
    if (cmd) {
        commands.push_back(cmd);
    }
}

void MacroCommand::setParseStrategy(AbstractParsingStrategy* strat) {
    strategy = strat;
}

void MacroCommand::displayInfo() {
    std::cout << "macro command executing " << commands.size()
              << " sub‑commands in sequence.\n";
}


int MacroCommand::execute(std::string input) {
    if (!strategy) {
        std::cerr << "MacroCommand: no parsing strat set \n";
        return mc_no_strat;
    }

    std::vector<std::string> parsed = strategy->parse(input);
    if (parsed.size() != commands.size()) {
        std::cerr << "MacroCommand: parse size mismatch \n";
        return mc_parse_size;
    }

    for (std::size_t i=NULL_DEFINITION; i < commands.size(); ++i) {
        int result = commands[i]->execute(parsed[i]);
        if (result != success) {
            return result;
        }
    }
    return success;
}