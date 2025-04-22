/*
 * ImageFile.h
 */

#pragma once
#include "AbstractFile.h"
#include <string>
#include <vector>

// Forward declaration for Visitor pattern if used
class AbstractFileVisitor;

class ImageFile : public AbstractFile { // Use public inheritance
private: // Make member variables private
    std::string name;
    std::vector<char> contents;
    unsigned int size; // Stores the dimension 'n'

public:
    // Constructor and Destructor
    ImageFile(std::string filename);
    ~ImageFile() override; // Good practice to have virtual destructor override

    // AbstractFile interface methods
    unsigned int getSize() override;
    std::string getName() override;
    int write(std::vector<char> input) override;
    int append(std::vector<char> input) override;

    // If AbstractFile.h must remain `void read()`, change this back and update .cpp
    void read() override; // As per current AbstractFile.h

    // Accept method for Visitor pattern (if needed)
    // virtual void accept(AbstractFileVisitor* visitor) override;

    // Helper method to get the dimension (optional, could be useful)
    // unsigned int getDimension() const { return size; }
};