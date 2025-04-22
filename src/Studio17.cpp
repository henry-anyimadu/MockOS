/**
*Studio 17 Main
 *
 **/

#include "mockos/AbstractFile.h"
#include "mockos/ImageFile.h"
#include "mockos/TextFile.h"

#include <iostream>

#include "mockos/SimpleFileSystem.h"


using namespace std;

std::vector<char> toVec(const std::string& s) {
    return {s.begin(), s.end()};
}

int main(int argc, char* argv[]) {

    //write an example image
    std::unique_ptr<AbstractFile> file = std::make_unique<ImageFile>("ImageFile.img");


    //form a good input
    std::vector<char> good3x3 = toVec(
        "XXX"
        "X X"
        "XXX"
        "3"
    );

    int write_result = file ->write(good3x3);
    file ->read();
    std::cout << "Write 1 Results: " << write_result << std::endl;

    //form an empty input (should print 1)
    std::vector<char> empty = toVec({});
    int write_result2 = file ->write(empty);
    file -> read();
    std::cout << "Write 2 Results: " << write_result2 << std::endl;

    //last char is not a digit (should print 2)
    std::vector<char> good3x3_2 = toVec(
            "XXX"
            "X X"
            "XXX"
        );
    int write_result3 = file -> write(good3x3_2);
    file -> read();
    std::cout << "Write 3 Results: " << write_result3 << std::endl;

    //size mismatch error (should print 3)
    std::vector<char> good3x3_3 = toVec(
    "XXX"
    "X X"
    "XXXX"
    "3"
        );
    int write_result4 = file -> write(good3x3_3);
    file -> read();
    std::cout << "Write 4 Results: " << write_result4 << std::endl;


    //Illegal Pixel Character (should print 4)
    std::vector<char> badPixel = toVec(
        "XXX"
        "X X"
        "XXX"
        "3"
    );
    badPixel[4] = 'Z'; //invalid pixel location for a 3x3 grid
    int write_result5 = file -> write(badPixel);
    file -> read();
    std::cout << "Write 5 Results: " << write_result5 << std::endl;

    //append shouldn't work (return 5)
    int write_result6 = file ->append(good3x3);
    file -> read();
    std::cout << "Write 6 Results: " << write_result6 << std::endl;



    //now lets start testing out the simple file system
    SimpleFileSystem sys = SimpleFileSystem();
    //add the Image file to the system

    //create a normal abstract pointer
    int result_abs = sys.addFile(file->getName(), file.release());
    if (result_abs!= success) {
        std::cerr << "addFile1 failed: " << result_abs << '\n';
        return result_abs;
    }
    cout << "File Added1" << endl;

    std::unique_ptr<AbstractFile> tfile = std::make_unique<TextFile>("notes.txt");
    int result_abs2 = sys.addFile(tfile->getName(),tfile.release());

    if (result_abs2!= success) {
        std::cerr << "addFile2 failed: " << result_abs << '\n';
        return result_abs;
    }
    cout << "File Added2" << endl;


    //testing open
    AbstractFile* h1 = sys.openFile("notes.txt");          // should succeed
    cout << "openFile 1  → " << (h1 ? "OK" : "nullptr") << '\n';
    AbstractFile* h2 = sys.openFile("ImageFile.img");
    cout << "openFile 2  → " << (h2 ? "OK" : "nullptr") << '\n';


    //testing close
    int c1 = sys.closeFile(h1);
    cout << "closeFile 1 → " << c1 << " (expected " << success << ")\n";
    int c2 = sys.closeFile(h2);
    cout << "closeFile 2 → " << c2 << " (expected " << success << ")\n";

    //try creating a file
    int create1 = sys.createFile("create.txt");
    cout << "Create File: " << create1  << endl;

    //delete all three files
    int d1 = sys.deleteFile("create.txt");
    cout << "Delete File1: " << d1 << endl;
    int d2 = sys.deleteFile("notes.txt");
    cout << "Delete File2: " << d2 << endl;
    int d3 = sys.deleteFile("ImageFile.img");
    cout << "Delete File3: " << d3 << endl;

    return success;
}