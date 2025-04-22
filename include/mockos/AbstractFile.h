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
};


class AbstractFile {
public:
    AbstractFile() = default;
    virtual ~AbstractFile()=0;
    virtual void read()=0;
    virtual int write(std::vector<char> input)=0;
    virtual int append(std::vector<char> input)=0;
    virtual unsigned int getSize()=0;
    virtual std::string getName()=0;
};
