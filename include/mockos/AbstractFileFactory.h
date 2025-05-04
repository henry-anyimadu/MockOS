/**
* Studios 16-21: AbstractFileFactory.h
 **/
#pragma once

#include "AbstractFile.h"
#include <string>
#include "mockos/Constants.h"

class AbstractFileFactory {
public:
    virtual ~AbstractFileFactory() = default;
    virtual AbstractFile* createFile(std::string filename) = NULL_DEFINITION;
};