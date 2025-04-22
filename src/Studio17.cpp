/**
*Studio 17 Main
 *
 **/

#include "mockos/AbstractFile.h"
#include "mockos/ImageFile.h"

#include <iostream>


std::vector<char> toVec(const std::string& s) {
    return {s.begin(), s.end()};
}

int main(int argc, char* argv[]) {

    //write an example image
    std::unique_ptr<AbstractFile> file = std::make_unique<ImageFile>("ImageFile");


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




    return 0;
}