/**
 *Studio 16-21: Abstract Interface
 */
#pragma once
#include <vector>


enum ErrorTypes {
    success,
    write_error,
};


class AbstractFile {
public:
    AbstractFile();
    virtual ~AbstractFile()=0;
    virtual void read()=0;
    virtual int write(std::vector<char> input)=0;
    virtual int append(std::vector<char> input)=0;
    virtual unsigned int getSize()=0;
    virtual std::string getName()=0;
};
