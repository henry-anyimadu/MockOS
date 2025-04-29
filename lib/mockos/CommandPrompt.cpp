#include "mockos/CommandPrompt.h"
#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFile.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

void CommandPrompt::setFileSystem(AbstractFileSystem* file_system) {
    objPointer = file_system;
}

void CommandPrompt::setFileFactory(AbstractFileFactory* file_factory) {
    objFactory = file_factory;
}

int CommandPrompt::addCommand(string params, AbstractCommand* cmd) {
    auto mapAns = cmdObjects.insert(make_pair(params, cmd));
    if (!mapAns.second) {
        return allocation_error;
    } else return success;
}


