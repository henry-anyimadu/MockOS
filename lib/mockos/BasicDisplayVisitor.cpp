/**
 *cpp file for BasicDisplayVistor, deriving from the File visitor interface
 *Allows you to visit both text and image files
 */



#include "mockos/BasicDisplayVisitor.h"
#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"
#include "mockos/Constants.h"
#include <iostream>
#include <cmath>


void BasicDisplayVisitor::visit_TextFile(TextFile* file) {
    std::vector<char> contents = file->read();
    for (char c : contents) {
        std::cout << c;
    }
}

void BasicDisplayVisitor::visit_ImageFile(ImageFile* file) {
    std::vector<char> contents = file->read();
    // Calculate size (dimension) based on content length
    unsigned int size = static_cast<unsigned int>(sqrt(contents.size()));

    // Format the image in a grid pattern
    for (unsigned int y = NULL_DEFINITION; y < size; ++y) {
        for (unsigned int x = NULL_DEFINITION; x < size; ++x) {
            unsigned int index = y * size + x;
            std::cout << contents[index];
        }
        std::cout << std::endl;
    }
}