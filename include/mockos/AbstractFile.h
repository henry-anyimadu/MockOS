/**
 *Studio 16-21: Abstract Interface
 */
#pragma once

#include <vector>

enum ErrorTypes {
    success,
    empty_error,
    no_digit_error,
    size_mismatch,
    pixel_error,
    append_error,
    duplicate_files,
    unknown_extension,
    allocation_error,
    file_already_exists,
    null_file_pointer,
    file_open_error,
    incorrect_password,
    ls_m_file_error,
    ls_m_extension_error,
    cat_file_error,
    cat_pointer_error,
    cat_ejection_error,
};

class AbstractFileVisitor; // Forward declaration needed

class AbstractFile {
public:
    AbstractFile() = default;
    virtual ~AbstractFile() = default;
    virtual std::vector<char> read() = 0; // Changed from void to vector<char>
    virtual int write(std::vector<char> input) = 0;
    virtual int append(std::vector<char> input) = 0;
    virtual unsigned int getSize() = 0;
    virtual std::string getName() = 0;
    virtual void accept(AbstractFileVisitor* visitor) = 0; // Added for Visitor pattern
};