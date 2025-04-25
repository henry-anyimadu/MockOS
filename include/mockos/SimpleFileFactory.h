/**
* Studios 16-21: SimpleFileFactory.h
 **/
#pragma once

#include "AbstractFileFactory.h"
#include <string>

class SimpleFileFactory : public AbstractFileFactory {
public:
    SimpleFileFactory() = default;
    ~SimpleFileFactory() override = default;
    AbstractFile* createFile(std::string filename) override;
};