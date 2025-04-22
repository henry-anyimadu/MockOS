/*
 * Studios 16-21 ImageFile.cpp
 */

#include "mockos/ImageFile.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath> // For sqrt

// Constructor: Initializes name and size (dimension) to 0.
ImageFile::ImageFile(std::string filename) : name(filename), size(0) {
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
    unsigned int empty = 0;
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
    for (unsigned int i = 0; i < expectedSize - 1; ++i) {
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
void ImageFile::read() {
    unsigned int empty = 0;
     if (size == empty) {
        return; // Nothing to print if size is 0
    }
    for (unsigned int y = 0; y < size; ++y) {
        for (unsigned int x = 0; x < size; ++x) {
            // Calculate index without bounds checking (assuming contents is correct size)
            unsigned int index = y * size + x;
            std::cout << contents[index];
        }
        std::cout << std::endl; // Newline after each row
    }
}
