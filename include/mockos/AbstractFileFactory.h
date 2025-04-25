/**
* Studios 16-21: AbstractFileFactory.h
 **/
#pragma once

#include "AbstractFile.h"
#include <string>

class AbstractFileFactory {
public:
    virtual ~AbstractFileFactory() = default;
    virtual AbstractFile* createFile(std::string filename) = 0;
};