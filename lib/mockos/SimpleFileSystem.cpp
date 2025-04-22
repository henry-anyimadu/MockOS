/**
 * Studios 16-21: SimpleFileSystem.cpp
 **/
#include "./mockos/SimpleFileSystem.h"
#include "./mockos/AbstractFileSystem.h"
#include <string>

using namespace std;


SimpleFileSystem::SimpleFileSystem() {
}

int SimpleFileSystem::addFile(string filename, AbstractFile *ptr) {
    if (ptr == nullptr) {
        return null_file_pointer;
    }

    if (files.count(filename) > 0) {
        return file_already_exists;
    }

    files.emplace(filename, ptr);
    return success;
}

AbstractFile *SimpleFileSystem::openFile(string filename) {
    // if !(files[filename]) {
    // return nullptr;
    // }
    if (files.count(filename) > 0) {
        return files[filename];
    }
}