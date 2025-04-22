/**
 *Text File
 */

#include "AbstractFile.h"

class TextFile: AbstractFile {
public:
    TextFile(std::string input);
    unsigned int getSize();
    std::string getName();
    std::vector<char> append();
    void read() override;
    void write();
private:
    std::string name;
    std::vector<char> contents;
};
