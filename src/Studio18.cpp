/**
* Studio 18 Main
 **/
#include "mockos/AbstractFile.h"
#include "mockos/AbstractFileSystem.h"
#include "mockos/SimpleFileSystem.h"
#include "mockos/AbstractFileFactory.h"
#include "mockos/SimpleFileFactory.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Create file system
    AbstractFileSystem* fs = new SimpleFileSystem();

    // Create file factory
    AbstractFileFactory* ff = new SimpleFileFactory();

    // Create and add files
    AbstractFile* textFile = ff->createFile("test.txt");
    if (textFile) {
        cout << "Successfully created text file: " << textFile->getName() << endl;
        fs->addFile(textFile->getName(), textFile);

        // Write to file
        vector<char> textData = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
        textFile->write(textData);

        // Read from file
        cout << "Contents of text file: ";
        textFile->read();
    } else {
        cout << "Failed to create text file" << endl;
    }

    AbstractFile* imageFile = ff->createFile("test.img");
    if (imageFile) {
        cout << "Successfully created image file: " << imageFile->getName() << endl;
        fs->addFile(imageFile->getName(), imageFile);

        // Write to file (valid 3x3 image)
        vector<char> imageData = {'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', '3'};
        imageFile->write(imageData);

        // Read from file
        cout << "Contents of image file:" << endl;
        imageFile->read();
    } else {
        cout << "Failed to create image file" << endl;
    }

    // Clean up
    delete fs;
    delete ff;

    return 0;
}