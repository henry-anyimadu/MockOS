/**
 *Text File as created in the studios
 *Simple file type for displaying plaintext
 */
#pragma once

#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
#include <string>

class TextFile: public AbstractFile {
public:
    TextFile(std::string input);
    unsigned int getSize() override;
    std::string getName() override;
    int append(std::vector<char> in) override;
    std::vector<char> read() override;
    int write(std::vector<char> in) override;
    void accept(AbstractFileVisitor* visitor) override;
    ~TextFile() override;
    AbstractFile* clone(std::string newName) const override;
private:
    std::string name;
    std::vector<char> contents;
};
