/*
 * Helper header including the tests for various data types
 * Lab 5 implementation for testing the commands in the file system
 */



#pragma once


#ifndef LAB5TESTS_H
#define LAB5TESTS_H

#include "AbstractFileSystem.h"
#include "TouchCommand.h"
#include "CopyCommand.h"
#include "DisplayCommand.h"
#include "LSCommand.h"
#include "RemoveCommand.h"

class Test {
public:
    static int runCopyTests(AbstractFileSystem* fs,
                            TouchCommand* touch,
                            CopyCommand*  cp);
    static int runTouchTests(AbstractFileSystem* fs,
                  TouchCommand*      touch);
    static int runRenameTests(AbstractFileSystem* fs,
                   TouchCommand*       touch,
                   AbstractCommand*    rn);
    static int runLSTests(AbstractFileSystem* fs,
                      TouchCommand* touch,
                      LSCommand* ls);

    static int runRemoveTests(AbstractFileSystem* fs,
                              TouchCommand* touch,
                              RemoveCommand* rm);

    static int runDisplayTests(AbstractFileSystem* fs,
                               TouchCommand* touch,
                               DisplayCommand* ds);

    static int runMacroTests();
};

#endif //LAB5TESTS_H
