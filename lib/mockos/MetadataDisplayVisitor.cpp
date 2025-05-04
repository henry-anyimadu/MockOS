/*
 *Implementation for the Display Visitor for metadata, derived from the interface for visitor types
 *Methods for text files and image files
 */


#include "mockos/MetadataDisplayVisitor.h"
#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"
#include <iostream>

void MetadataDisplayVisitor::visit_TextFile(TextFile* file) {
    std::cout << file->getName() << " text " << file->getSize() << std::endl;
}

void MetadataDisplayVisitor::visit_ImageFile(ImageFile* file) {
    std::cout << file->getName() << " image " << file->getSize() << std::endl;
}