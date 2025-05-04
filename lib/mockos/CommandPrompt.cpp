/*
 * Command Prompt implementation, allows for processing of cmds created in Lab5, and then also
 * modifiers like -@
 */




#include "mockos/CommandPrompt.h"
#include "mockos/Constants.h"

#include <iostream>

#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFile.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

// enum exitValues {
//     SUCCESS = 0,
//     MISC_FAIL = 1,
//     MAP_ERROR = 2,
//     QUIT = 420,
// };

CommandPrompt::CommandPrompt() : objPointer(nullptr), objFactory(nullptr) {}     // Initialize members to nullptr

CommandPrompt::CommandPrompt(AbstractFileSystem* fileSystem, AbstractFileFactory* fileFactory): objPointer(fileSystem), objFactory(fileFactory) {}

void CommandPrompt::setFileSystem(AbstractFileSystem* file_system) {
    objPointer = file_system;
}

void CommandPrompt::setFileFactory(AbstractFileFactory* file_factory) {
    objFactory = file_factory;
}

int CommandPrompt::addCommand(string params, AbstractCommand* cmd) {
    auto mapAns = cmdObjects.insert(make_pair(params, cmd));
    if (!mapAns.second) {
        return cmd_map_error;
    } else return success;
}

void CommandPrompt::listCommands() { // Prints the name of all the commands
    for (auto it = cmdObjects.begin(); it != cmdObjects.end(); ++it) {
        cout << it->first << endl;
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
    while (INF_LOOP) {
        string input = prompt();

        // Check if the input is "q", if it is quit and return an appropriate non-zero value
        if (input == "q") {
            return cmd_quit_signifier;
        }

        // If the input is "help", call the listCommands method
        if (input == "help") {
            listCommands();
            continue;
        }

        // Check if input contains a space (indicating more than one word)
        size_t spacePos = input.find(' ');

        if (spacePos == string::npos) {
            // Input is only 1 word (not "q" or "help")
            // Search the map of commands for the command that matches the input
            auto cmdIter = cmdObjects.find(input);

            if (cmdIter != cmdObjects.end()) {
                // If command is found, invoke execute with empty string
                int result = cmdIter->second->execute("");

                if (result != success) {
                    cout << "Command failed to execute. Result: " << result << endl;
                }
            } else {
                cout << "Command not found: " << input << endl;
            }
        } else {
            // Input is longer than 1 word
            // Extract the first word
            string firstWord = input.substr(NULL_DEFINITION, spacePos);

            if (firstWord == "help") {
                // If first word is "help", extract second string (command name)
                string commandName = input.substr(spacePos + 1);
                auto cmdIter = cmdObjects.find(commandName);

                if (cmdIter != cmdObjects.end()) {
                    // Call displayInfo() on the command
                    cmdIter->second->displayInfo();
                } else {
                    cout << "Command not found: " << commandName << endl;
                }
            } else {
                // First word is a command name
                auto cmdIter = cmdObjects.find(firstWord);

                if (cmdIter != cmdObjects.end()) {
                    // Pass remaining input as the parameter
                    string args = input.substr(spacePos + 1);
                    int result = cmdIter->second->execute(args);

                    if (result != success) {
                        cout << "Command failed to execute. Result: " << result << endl;
                    }
                } else {
                    cout << "Command not found: " << firstWord << endl;
                }
            }
        }
    }

    return success; // This line should never be reached
}

CommandPrompt::~CommandPrompt() {}