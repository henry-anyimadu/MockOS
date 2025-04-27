/*
 * Studio 20 Main Loop
 */

#include "mockos/AbstractFile.h"
#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"
#include "mockos/PasswordProxy.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    // Dynamically allocating a new file
    AbstractFile* nuclearLaunchCodes = new TextFile("secret.txt");

    // Password for our new file
    string password = "abc123";

    PasswordProxy *nuclearProxy = new PasswordProxy(nuclearLaunchCodes, password);

    cout << "New File Created: " << nuclearProxy->getName() << endl;

    // Attempt to write to the new file (should ask for password)
    cout << "Testing write operator for " << nuclearProxy->getName() << ": " << endl;
    vector<char> data = {'S', 't', 'r', 'i', 'n', 'g', '\0'};
    int result = nuclearProxy->write(data);
    vector<char> contents = nuclearProxy->read();

    if (result == 0) {
        cout << "Write Success" << endl;
        cout << "Content: ";
        string fileContent(contents.begin(), contents.end());
        cout << fileContent << endl;
    } else {
        cout << "Write Failed" << endl;
    }

    // Clean up resources
    cout << "Cleaning resources.. " << endl;
    delete nuclearProxy;

    cout << "Program Complete" << endl;
    return success;
}