/**
 *Studio 16-21: Abstract Interface
 *AbstractFile.h for defining the Abstract File class
 */
 // AbstractFile.h
  // Author: Kelenna, Henry, Jonah
  // Declaration of the AbstractFile interface. Defines common operations
  // for file types (read, write, append, getSize, getName). 
  // Includes support for Visitor (`accept`) and Prototype (`clone`) patterns. Defines error codes

#pragma once

#include <vector>
#include <string>
#include "mockos/Constants.h"

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
    dp_file_error,
    dp_ext_error,
    cp_token_error,
    cp_ext_error,
    cp_repeat_file,
    cp_pointer_error,
    cp_clone_error,
    mc_no_strat,
    mc_parse_size,
    cmd_map_error,
    cmd_quit_signifier,
};

class AbstractFileVisitor; // Forward declaration needed

class AbstractFile {
public:
    AbstractFile() = default;
    virtual ~AbstractFile() = default;
    virtual std::vector<char> read() = NULL_DEFINITION; // Changed from void to vector<char>
    virtual int write(std::vector<char> input) = NULL_DEFINITION;
    virtual int append(std::vector<char> input) = NULL_DEFINITION;
    virtual unsigned int getSize() = NULL_DEFINITION;
    virtual std::string getName() = NULL_DEFINITION;
    virtual void accept(AbstractFileVisitor* visitor) = NULL_DEFINITION; // Added for Visitor pattern
    virtual AbstractFile* clone(std::string newName) const = NULL_DEFINITION;
};