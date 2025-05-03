/*
 * Studios 16-21: AbstractFilesystem.h
 */
#pragma once

#include <filesystem>
#include <set>
#include "AbstractFile.h"

class AbstractFileSystem {
    public:
    virtual ~AbstractFileSystem() = default;
    virtual std::set<std::string> getFileNames() = 0;
    virtual int addFile(std::string filename, AbstractFile*) = 0;
    virtual int createFile(std::string filename) = 0;
    virtual int deleteFile(std::string filename) = 0;
    virtual AbstractFile* openFile(std::string filename) = 0;
    virtual int closeFile(AbstractFile*) = 0;

};
