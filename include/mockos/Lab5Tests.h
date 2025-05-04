#pragma once


#ifndef LAB5TESTS_H
#define LAB5TESTS_H

#include "AbstractFileSystem.h"
#include "TouchCommand.h"
#include "CopyCommand.h"

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
};

#endif //LAB5TESTS_H
