/**
* Studios 16-21: SimpleFileSystem.h
 **/
#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <set>
#include "AbstractFileSystem.h"

class SimpleFileSystem: AbstractFileSystem {
 public:
 SimpleFileSystem();
 ~SimpleFileSystem() override;

 // Delete copy constructor and assignment
 SimpleFileSystem(const SimpleFileSystem&) = delete;
 SimpleFileSystem& operator=(const SimpleFileSystem&) = delete;

 std::map<std::string, std::unique_ptr<AbstractFile>> files;
 std::set<std::string> openFiles;

 int addFile(std::string filename, AbstractFile *) override;
 int createFile(std::string filename) override;
 AbstractFile *openFile(std::string filename) override;
 int closeFile(AbstractFile *) override;
 int deleteFile(std::string filename) override;
};
