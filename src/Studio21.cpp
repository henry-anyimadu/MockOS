#include <iostream>

#include "mockos/AbstractFileFactory.h"
#include "mockos/AbstractFileSystem.h"
#include "mockos/CommandPrompt.h"
#include "mockos/SimpleFileFactory.h"
#include "mockos/SimpleFileSystem.h"
#include "mockos/TouchCommand.h"

int main() {
    // Dynamically allocate a SimpleFileSystem, a SimpleFileFactory, and a TouchCommand
    AbstractFileSystem* fileSystem = new SimpleFileSystem();
    AbstractFileFactory* fileFactory = new SimpleFileFactory();

    // Create the TouchCommand with the file system and factory
    TouchCommand* touchCommand = new TouchCommand(fileSystem, fileFactory);

    // Create a CommandPrompt and configure it
    CommandPrompt* cp = new CommandPrompt(fileSystem, fileFactory);

    // Add the touch command to the command prompt
    cp->addCommand("touch", touchCommand);






    // Run the command prompt
    cp->run();

    // After quitting, verify the touch command worked by trying to open a file
    // that was created during the session
    AbstractFile* testFile = fileSystem->openFile("test.txt");
    if (testFile != nullptr) {
        std::cout << "Successfully verified that the touch command created and added the file!" << std::endl;
        fileSystem->closeFile(testFile);
    } else {
        std::cout << "Could not verify that the touch command worked correctly." << std::endl;
    }

    // Clean up
    delete cp;
    delete fileSystem;
    delete fileFactory;

    return 0;
}
