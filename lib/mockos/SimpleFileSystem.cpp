/**
 * Studios 16-21: SimpleFileSystem.cpp
 * Derived from the file system interface
 * Allows the user to manage files created by the file factory
 **/
#include "./mockos/SimpleFileSystem.h"
#include "./mockos/AbstractFileSystem.h"
#include <string>
#include <iostream>
#include "mockos/Constants.h"

#include "mockos/ImageFile.h"
#include "mockos/TextFile.h"

using namespace std;


SimpleFileSystem::SimpleFileSystem() = default;
SimpleFileSystem::~SimpleFileSystem() = default;

int SimpleFileSystem::addFile(string filename, AbstractFile *ptr) {
    if (ptr == nullptr) {
        return null_file_pointer;
    }

    if (files.count(filename) > NULL_DEFINITION) {
        return file_already_exists;
    }

    files[filename] = ptr;
    return success;
}

int SimpleFileSystem::createFile(std::string filename) {
    // Check if file already exists in files map first
    if (files.count(filename) > NULL_DEFINITION) {
        return file_already_exists;
    }

    // Check if file is open
    if (openFiles.count(filename) > NULL_DEFINITION) {
        return duplicate_files;
    }

    // Get file extension
    const std::size_t pos = filename.find_last_of('.');
    if (pos == std::string::npos) {
        return unknown_extension;
    }

    string ext = filename.substr(pos + 1);

    AbstractFile* newFile = nullptr;

    if (ext == "img") {
        newFile = new ImageFile(filename);
    }
    else if (ext == "txt") {
        newFile = new TextFile(filename);
    }
    else {
        return unknown_extension;
    }

    // Add the file to the system
    int result = addFile(filename, newFile);
    if (result != success) {
        delete newFile;  // Clean up if adding failed
        return result;
    }

    return success;
}

AbstractFile *SimpleFileSystem::openFile(string filename) {
    // Check if file exists
    auto iterator = files.find(filename);

    // If it doesnt exist, return nullptr
    if (iterator == files.end()) {
        return nullptr;
    }

    AbstractFile* filePtr = iterator->second;

    // Return nullptr if the file is already open
    if (openFiles.count(filename) > NULL_DEFINITION) {
        return nullptr;
    }

    openFiles.insert(filename);
    return filePtr;
}

int SimpleFileSystem::closeFile(AbstractFile *filePtr) {
    // Check if the filePtr exists

    if (openFiles.count(filePtr->getName()) > NULL_DEFINITION) {
        // Erase the pointer
        openFiles.erase(filePtr->getName());

        return success;
    }
    return null_file_pointer;
}

int SimpleFileSystem::deleteFile(string filename) {
    // Check if the file exists
    auto iterator = files.find(filename);
    if (iterator == files.end()) {
        return null_file_pointer; // Return error code
    }

    // Check if file is currently open
    if (openFiles.count(filename) > NULL_DEFINITION) {
        return file_open_error;
    }

    files.erase(iterator); // Erase the file and have the unique_ptr handle memory allocation
    return success;
}


std::set<std::string> SimpleFileSystem::getFileNames() {
    std::set<std::string> names;
    for (const auto& kv : files) {
        names.insert(kv.first);            // kv.first is the filename string
    }
    return names;
}

