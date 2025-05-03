/*
* Lab 5: RemoveCommand cpp file
*/

#include "mockos/RemoveCommand.h"
#include "mockos/AbstractFile.h"
#include <iostream>

using namespace std;
RemoveCommand::RemoveCommand(AbstractFileSystem* fs) : fileSystem(fs) {}

void RemoveCommand::displayInfo() {
    cout << "remove deletes a file, invoke with: -rm <file>" << endl;
}


int RemoveCommand::execute(string fileName) {
    return fileSystem->deleteFile(fileName);
}
