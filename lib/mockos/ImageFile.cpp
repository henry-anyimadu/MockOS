/*
 * Studios 16-21 ImageFile.cpp
 * Allows for the creation of basic file type: image
 *
 */

#include "mockos/ImageFile.h"
#include "mockos/Constants.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath> // For sqrt

// Constructor: Initializes name and size (dimension) to 0.
ImageFile::ImageFile(std::string filename) : name(filename), size(NULL_DEFINITION) {
    // Initialize contents vector if needed, though it starts empty by default.
}

// Destructor (can be default if no specific cleanup is needed)
ImageFile::~ImageFile() = default;


// Returns the number of pixels (n*n)
unsigned int ImageFile::getSize() {
    return contents.size(); // The size of the vector storing the pixels
}

// Returns the filename
std::string ImageFile::getName() {
    return name;
}

// Writes data to the image file
int ImageFile::write(std::vector<char> input) {
    unsigned int empty = NULL_DEFINITION;
    if (input.empty()) {
        // Handle empty input if necessary, maybe return an error or do nothing
        contents.clear();
        size = empty;
        return empty_error; // Return a non-zero error code for empty input
    }

    // Extract the last character as the dimension character
    char sizeChar = input.back();

    // Check if the last character is a digit
    if (!isdigit(sizeChar)) {
         contents.clear();
         size = empty;
         return no_digit_error; // Error: size character is not a digit
    }

    // Convert the size character to an integer dimension 'n'
    int n = sizeChar - '0'; // ASCII trick: '3' - '0' = 3

    // Validate the input size
    // Expected size = n * n pixels + 1 size character
    unsigned int expectedSize = static_cast<unsigned int>(n * n + 1);
    if (input.size() != expectedSize) {
        // Size mismatch error
        contents.clear(); // Clear existing contents
        size = empty;         // Reset size dimension
        return size_mismatch; // Return a unique non-zero error code for size mismatch
    }

    // Validate pixel data (first n*n characters)
    for (unsigned int i = NULL_DEFINITION; i < expectedSize - 1; ++i) {
        if (input[i] != 'X' && input[i] != ' ') {
            // Invalid pixel error
            contents.clear(); // Clear existing contents
            size = empty;         // Reset size dimension
            return pixel_error; // Return a unique non-zero error code for invalid pixel
        }
    }

    // If validation passes, update the file's contents and size
    size = n; // Store the dimension 'n'
    contents.assign(input.begin(), input.end() - 1); // Copy pixel data (excluding the last size char)

    return success; // Return 0 for success
}

// Appending is not supported for ImageFile as per common image file formats
int ImageFile::append(std::vector<char> input) {
    // Return a non-zero error code indicating append is not supported
    return append_error; // Unique error code for unsupported operation
}

// Prints the image data to the console (formatted)
std::vector<char> ImageFile::read() {
    // Print the image (for backward compatibility with Studio 16-18 tests)
    // for (int y = 0; y < size; ++y) {
    //     for (int x = 0; x < size; ++x) {
    //         std::cout << contents[index(x, y)];
    //     }
    //     std::cout << '\n';
    // }
    return contents;
}

void ImageFile::accept(AbstractFileVisitor *visitor) {
    visitor->visit_ImageFile(this);
}


// ImageFile.cpp
#include <cmath>        // std::sqrt

AbstractFile* ImageFile::clone(std::string newName) const {
    // 1) allocate a fresh ImageFile
    auto* copy = new (std::nothrow) ImageFile(newName);
    if (!copy) return nullptr;

    // 2) rebuild the on‑disk format: pixels + dimension digit
    std::vector<char> buffer = contents;            // deep‑copy pixels
    unsigned int dim = static_cast<unsigned int>(std::sqrt(contents.size()));
    buffer.push_back(static_cast<char>('0' + dim)); // '2', '3', …

    // 3) write into the clone; abort if it fails
    if (copy->write(buffer) != success) {
        delete copy;
        return nullptr;
    }
    return copy;
}
