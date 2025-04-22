// SimpleFileSystem.cpp
#include "mockos/SimpleFileSystem.h"
#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"

using std::string;


SimpleFileSystem::SimpleFileSystem() = default;

SimpleFileSystem::~SimpleFileSystem() {
    for (auto& [name, ptr] : files) delete ptr;
    files.clear();
}

int SimpleFileSystem::addFile(string filename, AbstractFile* ptr)
{
    if (!ptr)
        return null_file_pointer;
    if (files.count(filename))
        return file_already_exists;

    files.emplace(std::move(filename), ptr);
    return success;
}


int SimpleFileSystem::createFile(string filename)
{
    if (files.count(filename))
        return duplicate_files;

    const std::size_t dot = filename.find_last_of('.');
    if (dot == string::npos || dot + 1 == filename.size())
        return unknown_extension;

    const string ext = filename.substr(dot + 1);

    AbstractFile* pf = nullptr;
    if (ext == "txt")      pf = new TextFile(filename);
    else if (ext == "img") pf = new ImageFile(filename);
    else                   return unknown_extension;

    return addFile(std::move(filename), pf);   // ownership pass  map
}

AbstractFile* SimpleFileSystem::openFile(string filename)
{
    auto it = files.find(filename);
    if (it == files.end())           return nullptr;          // no such file
    if (openFiles.count(filename))   return nullptr;          // already open

    openFiles.insert(filename);
    return it->second;
}

int SimpleFileSystem::closeFile(AbstractFile* ptr)
{
    if (!ptr) return null_file_pointer;

    const string& name = ptr->getName();
    auto it = openFiles.find(name);
    if (it == openFiles.end())       return open_file_error;

    openFiles.erase(it);
    return success;
}

int SimpleFileSystem::deleteFile(string filename)
{
    // 1. does it exist?
    auto it = files.find(filename);
    if (it == files.end()) return no_file_error;

    // 2. is it open?
    if (openFiles.count(filename)) return open_file_error;

    // 3. safe to delete
    delete it->second;
    files.erase(it);

    return success;
}
