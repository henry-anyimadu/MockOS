/*
 * Lab 20: PasswordProxy.cpp
 * Implementation for the Password proxy for studios and then also for cat command in labs
 */

#include "mockos/PasswordProxy.h"
#include "mockos/AbstractFile.h"
#include <iostream>
#include <limits>

using namespace std;

PasswordProxy::PasswordProxy(AbstractFile *file, string password) : protectedFile(file), password(password) {}

PasswordProxy::~PasswordProxy() {
    delete protectedFile;
}

// PasswordProxy.cpp
std::string PasswordProxy::passwordPrompt() {
    std::string input;
    std::cout << "Enter Password: ";
    std::getline(std::cin, input);
    return input;
}


vector<char> PasswordProxy::read() {
    string pw = passwordPrompt();
    if (pw == password) {
        return protectedFile->read();
    }
    return vector<char>();;
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



AbstractFile* PasswordProxy::clone(std::string newName) const {
    // 1) delegate cloning of the actual data
    AbstractFile* clonedInner = protectedFile->clone(newName);
    if (clonedInner == nullptr) return nullptr;

    // 2) wrap the clone in a new proxy that uses the same password
    return new (std::nothrow) PasswordProxy(clonedInner, password);
}

