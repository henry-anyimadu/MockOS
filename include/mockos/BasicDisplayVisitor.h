/*
 *Lab 5: Basic Display Visitor
 *Derives from AbstractFileVisitor for Basic Data types
 */
 // Author: Kelenna, Henry, Jonah
 //Declaration of the BasicDisplayVisitor class. Implements AbstractFileVisitor
 // to display the formatted contents of TextFile and ImageFile objects.

#pragma once
#include "AbstractFileVisitor.h"

class BasicDisplayVisitor : public AbstractFileVisitor {
public:
    void visit_TextFile(TextFile* file) override;
    void visit_ImageFile(ImageFile* file) override;
};