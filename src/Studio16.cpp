/**
 *Studio 16 Main
 *
 **/


#include "mockos/AbstractFile.h"
#include "mockos/TextFile.h"
#include <memory>

using namespace std;

int main(int argc, char* argv[]) {
    TextFile t = TextFile("Textfile");

    //build up a test file
    const std::string literal = "Testing!\n";
    std::vector<char> data1(literal.begin(), literal.end());

    //write to the file
    t.write(data1);

    //read the file
    t.read();

    //test the append function
    const std::string append = "Append.\n";
    const std::vector<char> data2(append.begin(),append.end());
    t.append(data2);


    //read again
    t.read();



    //now create a file type from the abstract class
    std::unique_ptr<AbstractFile> file = std::make_unique<TextFile>("Textfile");
    const string literal2 = "Testing the Polymorphism!\n";
    const vector<char> data3(literal2.begin(), literal2.end());
    file->write(data3);

    file->read();

    //testing append for the polymorphism
    const string append2 = "Testing the Polymorphism Append.\n";
    const vector<char> data4(append2.begin(), append2.end());
    file->append(data4);

    file->read();





    return success;
}


