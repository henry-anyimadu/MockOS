/*
 * Studios 16-21: AbstractFilesystem.h
 */
#pragma once

#include <filesystem>
#include "AbstractFile.h"

class AbstractFileSystem {
    public:
    virtual int addFile(std::string filename, AbstractFile*);
    virtual int createFile(std::string filename);
    virtual int deleteFile(std::string filename);
    virtual AbstractFile* openFile(std::string filename);
    virtual int closeFile(AbstractFile*);
};
