/**
*Studio 16-21: Text File Cpp
 */

#include "mockos/TextFile.h"

TextFile::TextFile(std::string input):name(input) {
}

unsigned int TextFile::getSize() {
  return contents.size();
}





