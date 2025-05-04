#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>

#include "mockos/AbstractFileFactory.h"
#include "mockos/AbstractFileSystem.h"
#include "mockos/CatCommand.h"
#include "mockos/CommandPrompt.h"
#include "mockos/CopyCommand.h"
#include "mockos/DisplayCommand.h"
#include "mockos/SimpleFileFactory.h"
#include "mockos/SimpleFileSystem.h"
#include "mockos/TouchCommand.h"
#include "mockos/LSCommand.h"
#include "mockos/RemoveCommand.h"
#include "mockos/TextFile.h"
#include "mockos/PasswordProxy.h"



int runCopyTests(AbstractFileSystem* fs,
                 TouchCommand* touch,
                 CopyCommand*  cp)
{
    int failures = 0;
    const int OK = 0;

    //---------------- 1. text file ----------------
    assert(touch->execute("orig.txt") == OK);
    if (auto* f = fs->openFile("orig.txt")) {
        f->write({'H','e','l','l','o','\n'});
        fs->closeFile(f);
    }

    assert(cp->execute("orig.txt orig_copy") == OK);

    auto* orig = fs->openFile("orig.txt");
    auto* copy = fs->openFile("orig_copy.txt");
    if (!orig || !copy) ++failures;
    else {
        if (orig->read() != copy->read()) ++failures;
        copy->append({'B','y','e','\n'});
        if (orig->read() == copy->read()) ++failures;
    }
    if (orig) fs->closeFile(orig);
    if (copy) fs->closeFile(copy);

    //---------------- 2. image file ---------------
    assert(touch->execute("pict.img") == OK);
    if (auto* f = fs->openFile("pict.img")) {
        f->write({'X','X','X','X','2'});     // 2×2
        fs->closeFile(f);
    }

    assert(cp->execute("pict.img pict_copy") == OK);

    auto* pict     = fs->openFile("pict.img");
    auto* pictCopy = fs->openFile("pict_copy.img");
    if (!pict || !pictCopy || pict->read() != pictCopy->read()) ++failures;
    if (pict)     fs->closeFile(pict);
    if (pictCopy) fs->closeFile(pictCopy);

    //---------------- 3. password‑protected -------
    {
        auto* raw = new TextFile("secret.txt");
        raw->write({'1','2','3'});
        auto* prox = new PasswordProxy(raw, "pw");
        fs->addFile("secret.txt", prox);

        if (cp->execute("secret.txt secret_copy") != OK) ++failures;

        auto* scopy = fs->openFile("secret_copy.txt");
        if (!scopy) ++failures;
        else        fs->closeFile(scopy);

        auto* sorig = fs->openFile("secret.txt");
        if (sorig)  fs->closeFile(sorig);
    }

    return failures;
}


//--------------------------------------------------------------
//  Helper: automated tests for TouchCommand
//--------------------------------------------------------------
int runTouchTests(AbstractFileSystem* fs,
                  TouchCommand*      touch)
{
    int failures = 0;
    const int OK          = 0;
    const int ERR_EXISTS  = file_already_exists;
    const int ERR_UNKNOWN = allocation_error;

    // 1. create .txt
    if (touch->execute("alpha.txt") != OK) ++failures;
    if (auto* f = fs->openFile("alpha.txt")) {
        fs->closeFile(f);
    } else ++failures;

    // 2. duplicate name
    if (touch->execute("alpha.txt") != ERR_EXISTS) ++failures;

    // 3. create .img
    if (touch->execute("beta.img") != OK) ++failures;
    if (auto* f = fs->openFile("beta.img")) {
        fs->closeFile(f);
    } else ++failures;

    // 4. bad extension
    if (touch->execute("gamma.xyz") != ERR_UNKNOWN) ++failures;

    return failures;
}





int main() {
    // Dynamically allocate a SimpleFileSystem, a SimpleFileFactory, and a TouchCommand
    AbstractFileSystem* fileSystem = new SimpleFileSystem();
    AbstractFileFactory* fileFactory = new SimpleFileFactory();

    // Create the TouchCommand with the file system and factory
    TouchCommand* touchCommand = new TouchCommand(fileSystem, fileFactory);

    // Create RemoveCommand w/ the file system
    RemoveCommand* removeCommand = new RemoveCommand(fileSystem);

    //Create the LSCommand with the file system
    LSCommand* lsCommand = new LSCommand(fileSystem);


    //Create the cat command with the file system
    CatCommand* catcommand = new CatCommand(fileSystem);


    //create the display command with the file system
    DisplayCommand* dscommand = new DisplayCommand(fileSystem);


    //create the copy command with the file system
    CopyCommand* cpcommand = new CopyCommand(fileSystem);

    // Create a CommandPrompt and configure it
    CommandPrompt* cp = new CommandPrompt(fileSystem, fileFactory);

    // Add the touch command to the command prompt
    cp->addCommand("touch", touchCommand);

    // Add the LS command to the command prompt
    cp->addCommand("ls",lsCommand);

    // Adds remove to cmd
    cp->addCommand("rm",removeCommand);

    //Adds cat to cmd
    cp->addCommand("cat",catcommand);

    //Adds display to cmd
    cp->addCommand("ds",dscommand);

    //adds cp to cmd
    cp->addCommand("cp",cpcommand);





    if (int fails = runCopyTests(fileSystem, touchCommand, cpcommand))
        std::cout << "[CopyCommand tests] FAILED: " << fails << '\n';
    else
        std::cout << "[CopyCommand tests] all passed\n";


    if (int fails = runTouchTests(fileSystem, touchCommand))
        std::cout << "[TouchCommand tests] FAILED: " << fails << '\n';
    else
        std::cout << "[TouchCommand tests] all passed\n";


    // Run the command prompt
    cp->run();


    // Clean up
    delete cp;
    delete fileSystem;
    delete fileFactory;

    return 0;
}