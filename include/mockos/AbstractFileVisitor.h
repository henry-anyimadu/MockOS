/*
 *Lab 5: Abstract File Visitor Header
 *Allows you to visit both file types
 */
// Author: Kelenna, Henry, Jonah
// Declaration of the AbstractFileVisitor interface (Visitor pattern).
// Defines the contract for visitors performing operations on concrete file types.
// Requires visit methods for each concrete file type.



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