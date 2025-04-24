/**
*Studio 17 Main
 *
 **/

#include "mockos/AbstractFile.h"
#include "mockos/ImageFile.h"

#include <iostream>

#include "mockos/SimpleFileSystem.h"
#include "mockos/TextFile.h"

using namespace std;

// Helper function to convert string to vector<char>
vector<char> stringToVector(const string& str) {
    return {str.begin(), str.end()};
}

std::vector<char> toVec(const std::string& s) {
    return {s.begin(), s.end()};
}

int main(int argc, char* argv[]) {
    // Test the SimpleFileSystem in this studio specifically
    SimpleFileSystem sys;
    cout << "--Testing SimpleFileSystem--" << endl;

    auto* text_file = new TextFile("poem.txt");
    auto* image_file = new ImageFile("painting.img");

    // addFile
    cout << "--AddFile--" << endl;

    int result = sys.addFile(text_file->getName(), text_file);
    cout << "Result from adding a text file: " << result << endl;

    result = sys.addFile(image_file->getName(), image_file);
    cout << "Result from adding a image file: " << result << endl;

    // createFile
    cout << "--CreateFile--" << endl;
    result = sys.createFile("lab.txt");
    cout << "Text result from createFile: " << result << endl;
    result = sys.createFile("4o.img");
    cout << "Image Result from createFile: " << result << endl;

    // This should fail (unrecognized extension)
    result = sys.createFile("poem.mp3");
    cout << "This should be non-zero: " << result << endl;

    // Testing file operations: open, write, read, close
    cout << "\n-- Testing text file operations --" << endl;
    AbstractFile* openedFile = sys.openFile("lab.txt");
    if (openedFile != nullptr) {
        cout << "Successfully opened sample text file" << endl;

        // Write to the file
        vector<char> content = stringToVector("Hello, this is a test file!");
        result = openedFile->write(content);
        cout << "Writing to file result: " << endl;

        // Read from the file
        cout << "File content: ";
        openedFile->read();

        // Close the file
        result = sys.closeFile(openedFile);
        cout << "Closing file result: " << endl;
    } else {
        cout << "Failed to open sample text file" << endl;
    }
    return success;
}