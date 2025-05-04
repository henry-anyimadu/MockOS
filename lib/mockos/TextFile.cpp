/**
*Studio 16-21: Text File Cpp
*Simple file type for plaintext
 */

#include "mockos/TextFile.h"
#include "mockos/AbstractFileVisitor.h"
#include <iostream>


using namespace std;

TextFile::TextFile(string input):name(input) {
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

// vector<char> TextFile::read() {
//     // ensure C-string termination
//     if (contents.empty() || contents.back() != '\0')
//         contents.push_back('\0');
//     return contents;
// }


vector<char> TextFile::read() {
    // Print the content (for backward compatibility with Studio 16-18 tests)
    // for (char c : contents)
    //     std::cout << c;

    return contents;
}


void TextFile::accept(AbstractFileVisitor *visitor) {
    visitor->visit_TextFile(this);
}


TextFile::~TextFile() = default;

AbstractFile* TextFile::clone(std::string newName) const {
    TextFile* copy = new TextFile(newName);
    copy->write(contents);          // deep‑copy the bytes
    return copy;
}















