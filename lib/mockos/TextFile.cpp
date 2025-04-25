/**
*Studio 16-21: Text File Cpp
 */

#include "mockos/TextFile.h"
#include "mockos/AbstractFileVisitor.h"
#include <iostream>


using namespace std;

TextFile::TextFile(std::string input):name(input) {
}

unsigned int TextFile::getSize() {
  return contents.size();
}


std::string TextFile::getName() {
    return name;
}

int TextFile::write(std::vector<char> in) {
    contents = in;
    if (in.empty()) {
        return empty_error;
    }
    //then we have copied correctly
    return success;
}

int TextFile::append(std::vector<char> in) {
    for (char i : in) {
        contents.push_back(i);
    }
    return success;
}

vector<char> TextFile::read() {
    return contents;
}

void TextFile::accept(AbstractFileVisitor *visitor) {
    visitor->visit_TextFile(this);
}


TextFile::~TextFile() {}















