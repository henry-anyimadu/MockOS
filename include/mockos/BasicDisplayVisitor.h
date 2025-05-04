/*
 *Lab 5: Basic Display Visitor
 *Derives from AbstractFileVisitor for Basic Data types
 */

#pragma once
#include "AbstractFileVisitor.h"

class BasicDisplayVisitor : public AbstractFileVisitor {
public:
    void visit_TextFile(TextFile* file) override;
    void visit_ImageFile(ImageFile* file) override;
};