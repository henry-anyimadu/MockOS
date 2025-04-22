/**
* Studios 16-21: SimpleFileSystem.h
 **/
#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <set>
#include "AbstractFileSystem.h"

class SimpleFileSystem: public AbstractFileSystem {
 public:
 SimpleFileSystem();
 ~SimpleFileSystem();

 std::map<std::string, AbstractFile*> files;
 std::set<std::string> openFiles;

 int addFile(std::string filename, AbstractFile *) override;
 int createFile(std::string filename) override;
 AbstractFile *openFile(std::string filename) override;
 int closeFile(AbstractFile *) override;
 int deleteFile(std::string filename) override;
};
