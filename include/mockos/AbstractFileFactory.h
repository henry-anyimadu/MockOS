/**
* Studios 16-21: AbstractFileFactory.h
 **/
 
// Author: Kelenna, Henry, Jonah
// Declaration of the AbstractFileFactory interface (Abstract Factory pattern)
// Defines the contract for creating AbstractFile objects 
// Decouples file creation from file system/client
#pragma once

#include "AbstractFile.h"
#include <string>
#include "mockos/Constants.h"

class AbstractFileFactory {
public:
    virtual ~AbstractFileFactory() = default;
    virtual AbstractFile* createFile(std::string filename) = NULL_DEFINITION;
};