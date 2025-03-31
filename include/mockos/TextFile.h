/**
 *Text File
 */

#include "AbstractFile.h"

class TextFile: AbstractFile {
public:
    TextFile(std::string input);
    unsigned int getSize();
private:
    std::string name;
    std::vector<char> contents;
};
