/*
 * TouchCommand cpp file for file creation
 */

#include "mockos/TouchCommand.h"
#include "mockos/AbstractCommand.h"
#include <iostream>

AbstractCommand::AbstractCommand() {}

TouchCommand::TouchCommand(AbstractFileSystem* fileSys, AbstractFileFactory* fileFact)
    : fileSystem(fileSys), fileFactory(fileFact) {}

void TouchCommand::displayInfo() {
    std::cout << "touch creates a file, touch can be invoked with the command: touch <filename>" << std::endl;
}

int TouchCommand::execute(std::string filename) {
    // Create the file using the file factory
    //THIS LINE IS FAILING
    AbstractFile* file = fileFactory->createFile(filename);

    // If file creation failed, return an error
    if (file == nullptr) {
        return allocation_error;
    }

    // Add the file to the file system
    int result = fileSystem->addFile(file->getName(), file);


    // If adding to file system failed, delete the file and return an error
    if (result != success) {
        delete file;
        return result;
    }

    return success;
}