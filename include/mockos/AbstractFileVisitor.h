// include/mockos/AbstractFileVisitor.h
#pragma once

// Forward declarations
class TextFile;
class ImageFile;

class AbstractFileVisitor {
public:
    virtual ~AbstractFileVisitor() = default;
    virtual void visit_TextFile(TextFile* file) = 0;
    virtual void visit_ImageFile(ImageFile* file) = 0;
};