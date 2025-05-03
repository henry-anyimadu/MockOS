/*
* CatCommand.cpp
 */

#include "mockos/CatCommand.h"
#include <iostream>
#include <sstream>
#include <vector>

CatCommand::CatCommand(AbstractFileSystem* fs) : fileSystem(fs) {}

auto isImageFile = [](const std::string& name) {
    return name.size() >= 4 &&
           name.compare(name.size() - 4, 4, ".img") == 0;
};


void CatCommand::displayInfo() {
    std::cout << "Concatenate/Edit a file\n"
                 "Usage:\n"
                 "  cat <filename>       (overwrite)\n"
                 "  cat <filename> -a    (append)\n"
                 "Inside the editor type lines of text followed by:\n"
                 "  :wq   save & quit\n"
                 "  :q    quit without saving\n";
}



int CatCommand::execute(std::string args) {
    //Parse the args
    std::istringstream parser(args);
    std::string filename, flag;
    parser >> filename;
    if (filename.empty()) return cat_file_error;


    bool appendMode = false;
    if (parser >> flag) {
        if (flag == "-a") appendMode = true;
        else    return cat_file_error;
    }

    //Too many tokens
    if (parser >> flag) return cat_file_error;


    //open the file
    AbstractFile* fileptr = fileSystem->openFile(filename);
    if (fileptr == nullptr) {
        std::cerr << "cat: cannot open \"" << filename << "\"\n";
        return cat_pointer_error;
    }

    //if we are in append mode (-a), we show the current contents
    if (appendMode) {
        for (char c : fileptr -> read()) {
            std::cout << c;
        }
        std::cout << '\n';
    }



    //Read the user input (to concact)
    std::vector<char> buf;
    std::string line;
    while (std::getline(std::cin,line)) {
        if (line == ":q") {
            //q has been inputted by the user, close without saving
            fileSystem->closeFile(fileptr);
            return success;
        }
        if (line == ":wq") {
            // ------- NEW: tidy buffer before saving -----------
            if (isImageFile(filename)) {
                // remove *all* new‑lines for .img
                buf.erase(std::remove(buf.begin(), buf.end(), '\n'), buf.end());
            } else if (!buf.empty() && buf.back() == '\n') {
                // drop just the final newline for text
                buf.pop_back();
            }
            // ---------------------------------------------------

            int res = appendMode ? fileptr->append(buf)
                                 : fileptr->write(buf);
            fileSystem->closeFile(fileptr);
            return res;
        }
        buf.insert(buf.end(), line.begin(), line.end());
        buf.push_back('\n');          // keep newline between user lines
    }

    //NO wq or q, reached EOF
    fileSystem->closeFile(fileptr);
    return cat_ejection_error;



}




