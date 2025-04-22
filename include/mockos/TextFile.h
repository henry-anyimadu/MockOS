/**
 *Text File
 */

#include "AbstractFile.h"

class TextFile: public AbstractFile {
public:
    TextFile(std::string input);
    unsigned int getSize() override;
    std::string getName() override;
    int append(std::vector<char> in) override;
    void read() override;
    int write(std::vector<char> in) override;
    ~TextFile() override;
private:
    std::string name;
    std::vector<char> contents;
};
