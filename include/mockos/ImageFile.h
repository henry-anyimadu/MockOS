/*
 * ImageFile.h, as implemented in the studios
 */

#pragma once
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
#include <string>
#include <vector>

// Forward declaration for Visitor pattern if used
class AbstractFileVisitor;

class ImageFile : public AbstractFile { // Use public inheritance
private: // Make member variables private
    std::string name;
    std::vector<char> contents;
    unsigned int size; // Stores the dimension 'n'
    std::size_t index(int x, int y) const {
        // y * width + x
        return static_cast<std::size_t>(y) * size + static_cast<std::size_t>(x);
    }

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
    std::vector<char> read() override; // Updated in studio 19

    // Accept method for Visitor pattern (if needed)
    void accept(AbstractFileVisitor* visitor) override;

    //Helper method to clone for cp
    AbstractFile* clone(std::string newName) const override;

};