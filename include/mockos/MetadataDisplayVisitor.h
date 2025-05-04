/*
 * Dervied from the Abstract filevisitor interface
 * Part of lab 5, and getting the data for the ls command
 */

#pragma once
#include "AbstractFileVisitor.h"

class MetadataDisplayVisitor : public AbstractFileVisitor {
public:
    void visit_TextFile(TextFile* file) override;
    void visit_ImageFile(ImageFile* file) override;
};