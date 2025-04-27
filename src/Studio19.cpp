/*
 * Studio 19 Main Loop
 */

#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"
#include "mockos/BasicDisplayVisitor.h"
#include "mockos/MetadataDisplayVisitor.h"
#include <iostream>

int main() {
    // Create a text file
    TextFile textFile("sample.txt");
    std::vector<char> textContent = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    textFile.write(textContent);

    // Create an image file (3×3)
    ImageFile imageFile("sample.img");
    std::vector<char> imageContent = {'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', '3'};
    imageFile.write(imageContent);

    // Display file contents using visitors
    std::cout << "Basic Display of Text File:" << std::endl;
    BasicDisplayVisitor bdv;
    textFile.accept(&bdv);
    std::cout << std::endl;

    std::cout << "Basic Display of Image File:" << std::endl;
    imageFile.accept(&bdv);

    // Display file metadata
    std::cout << "Metadata Display:" << std::endl;
    MetadataDisplayVisitor mdv;
    textFile.accept(&mdv);
    imageFile.accept(&mdv);

    return 0;
}