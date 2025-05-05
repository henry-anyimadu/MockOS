/*
 * Studios 16-21: AbstractFilesystem.h
 * Interface for the file system
 */
 
// Author: Kelenna, Henry, Jonah
// Declaration of the AbstractFileSystem interface. 
// Defines the contract for file system implementations (managing files: add, delete, open, close).
#pragma once

#include <set>
#include <string>
#include "AbstractFile.h"
#include "mockos/Constants.h"

class AbstractFileSystem {
    public:
    virtual ~AbstractFileSystem() = default;
    virtual std::set<std::string> getFileNames() = NULL_DEFINITION;
    virtual int addFile(std::string filename, AbstractFile*) = NULL_DEFINITION;
    virtual int createFile(std::string filename) = NULL_DEFINITION;
    virtual int deleteFile(std::string filename) = NULL_DEFINITION;
    virtual AbstractFile* openFile(std::string filename) = NULL_DEFINITION;
    virtual int closeFile(AbstractFile*) = NULL_DEFINITION;

};
