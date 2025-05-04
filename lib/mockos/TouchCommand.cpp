/*
 * TouchCommand cpp file for file creation
 * Implementation of the command, with password protection
 */

#include "mockos/TouchCommand.h"
#include "mockos/AbstractCommand.h"
#include <iostream>
#include <sstream>

#include "mockos/PasswordProxy.h"

AbstractCommand::AbstractCommand() {}

TouchCommand::TouchCommand(AbstractFileSystem* fileSys, AbstractFileFactory* fileFact)
    : fileSystem(fileSys), fileFactory(fileFact) {}

void TouchCommand::displayInfo() {
    std::cout << "touch creates a file, touch can be invoked with the command: touch <filename>" << std::endl;
    std::cout << " Create a password-protected file w/ touch <filename> -p" << std::endl;
}

int TouchCommand::execute(std::string input) {
    std::istringstream parser(input);
    std::string filename, flag;
    int result = success; // Initialize result
    parser >> filename;
    bool needsPassword = false;

    // check if '-p' exists
    if (parser >> flag) {
        if (flag == "-p") needsPassword = true;
    }

    // Create the file using the file factory
    AbstractFile* file = fileFactory->createFile(filename);

    // If file creation failed, return an error
    if (file == nullptr) {
        return allocation_error;
    }

    if (needsPassword) {
        std::string password;

        // Prompt for password
        std::cout << "Enter Password: ";
        getline(std::cin, password);

        // Initialize PasswordProxy
        PasswordProxy* newFile = new PasswordProxy(file, password);
        result = fileSystem->addFile(newFile->getName(), newFile); // Add the proxy

        if (result != success) {
            delete newFile; // This will also delete the wrapped file
            return result;
        }

        std::cout << "File Created" << std::endl;
    } else {
        // Add the file to the file system
        result = fileSystem->addFile(file->getName(), file);

        if (result != success) {
            delete file;
            return result;
        }

        std::cout << "File Added" << std::endl;
    }

    return success;

}