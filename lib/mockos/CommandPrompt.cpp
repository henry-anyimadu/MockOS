#include "mockos/CommandPrompt.h"

#include <iostream>

#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFile.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

enum exitValues {
    SUCCESS = 0,
    MISC_FAIL = 1,
    MAP_ERROR = 2,
    QUIT = 420,
};

CommandPrompt::CommandPrompt(AbstractFileSystem *, AbstractFileFactory *): objPointer(nullptr), objFactory(nullptr) {}

void CommandPrompt::setFileSystem(AbstractFileSystem* file_system) {
    objPointer = file_system;
}

void CommandPrompt::setFileFactory(AbstractFileFactory* file_factory) {
    objFactory = file_factory;
}

int CommandPrompt::addCommand(string params, AbstractCommand* cmd) {
    auto mapAns = cmdObjects.insert(make_pair(params, cmd));
    if (!mapAns.second) {
        return MAP_ERROR;
    } else return SUCCESS;
}

void CommandPrompt::listCommands() { // Prints the name of all the commands
    for (auto it = cmdObjects.begin(); it != cmdObjects.end(); it++) {
        cout << it->first << endl; // Might need to print second as well, but we'll see
    }
}

string CommandPrompt::prompt() {
    cout << "Enter a command, q to quit, help for a list of commands, or help" << endl;
    cout << " followed by a command name for more information about that command." << endl;
    cout << "$   ";
    string input;
    getline(cin, input);
    return input;
}

int CommandPrompt::run() {
    while (1) {
        string input = prompt();
        if (input == "q") {
            return QUIT;
        }
        if (input == "help") {
            listCommands();
        }

    }
}
CommandPrompt::~CommandPrompt() {}
