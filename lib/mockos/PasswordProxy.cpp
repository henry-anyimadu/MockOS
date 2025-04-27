/*
 * Lab 20: PasswordProxy.cpp
 */

#include "mockos/PasswordProxy.h"
#include "mockos/AbstractFile.h"
#include <iostream>

using namespace std;

PasswordProxy::PasswordProxy(AbstractFile *file, string password) : protectedFile(file), password(password) {}

PasswordProxy::~PasswordProxy() {
    delete protectedFile;
}

string PasswordProxy::passwordPrompt() {
    string input;
    cout << "Enter Password: ";
    cin >> input;
    return input;
}

vector<char> PasswordProxy::read() {
    string pw = passwordPrompt();
    if (pw == password) {
        return protectedFile->read();
    }
}

int PasswordProxy::write(vector<char> input) {
    string pw = passwordPrompt();
    if (pw == password) {
        return protectedFile->write(input);
    }
    return incorrect_password; // Only if password is incorrect
}

int PasswordProxy::append(std::vector<char> input) {
    string pw = passwordPrompt();
    if (pw == password) {
        return protectedFile->append(input);
    }
    return incorrect_password;
}

unsigned int PasswordProxy::getSize() {
    return protectedFile->getSize();
}

std::string PasswordProxy::getName() {
    return protectedFile->getName();
}

void PasswordProxy::accept(AbstractFileVisitor *visitor) {
    string pw = passwordPrompt();
    if (pw == password) {
        protectedFile->accept(visitor);
    }
}


