/*
 * Lab 20: PasswordProxy.h
 * Defines the password logic for Lab 5 as well
 */

#pragma once

#include "AbstractFile.h"
#include <string>

class PasswordProxy: public AbstractFile {
private:
    AbstractFile* protectedFile;
    std::string password;

protected:
    std::string passwordPrompt();

public: // Constructors
    PasswordProxy(AbstractFile* file, std::string password);
    ~PasswordProxy() override;

    std::vector<char> read() override;
    int write(std::vector<char> input) override;
    int append(std::vector<char> input) override;
    unsigned int getSize() override;
    std::string getName() override;
    void accept(AbstractFileVisitor* visitor) override;
    AbstractFile* clone(std::string newName) const override;
};