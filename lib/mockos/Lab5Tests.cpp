//
// Lab5Tests.cpp: This file holds our unit tests for Lab 5. These methods test the commands we have
// implemented throughout the course of this lab.
//


#include <cassert>
#include <iostream>
#include <sstream>

#include "mockos/TextFile.h"
#include "mockos/Lab5Tests.h"

#include "mockos/MacroCommand.h"
#include "mockos/PasswordProxy.h"
#include "mockos/Constants.h"
#include "mockos/RenameParsingStrategy.h"


int Test::runCopyTests(AbstractFileSystem* fs, TouchCommand* touch, CopyCommand* cp)
{
    int failures = NULL_DEFINITION;
    const int OK = NULL_DEFINITION;

    // 1. text file
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

    // 2. image file
    assert(touch->execute("pict.img") == OK);
    if (auto* f = fs->openFile("pict.img")) {
        f->write({'X','X','X','X','2'}); // 2×2
        fs->closeFile(f);
    }

    assert(cp->execute("pict.img pict_copy") == OK);

    auto* pict = fs->openFile("pict.img");
    auto* pictCopy = fs->openFile("pict_copy.img");
    if (!pict || !pictCopy || pict->read() != pictCopy->read()) ++failures;
    if (pict) fs->closeFile(pict);
    if (pictCopy) fs->closeFile(pictCopy);

    // 3. password‑protected
    {
        auto* raw = new TextFile("secret.txt");
        raw->write({'1','2','3'});
        auto* prox = new PasswordProxy(raw, "pw");
        fs->addFile("secret.txt", prox);

        if (cp->execute("secret.txt secret_copy") != OK) ++failures;

        auto* scopy = fs->openFile("secret_copy.txt");
        if (!scopy) ++failures;
        else fs->closeFile(scopy);

        auto* sorig = fs->openFile("secret.txt");
        if (sorig) fs->closeFile(sorig);
    }

    return failures;
}

//  Helper: automated tests for TouchCommand
int Test::runTouchTests(AbstractFileSystem* fs, TouchCommand* touch)
{
    int failures = NULL_DEFINITION;
    const int OK = NULL_DEFINITION;
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

//  Helper: automated tests for Rename (rn) MacroCommand
int Test::runRenameTests(AbstractFileSystem* fs, TouchCommand* touch, AbstractCommand* rn)   // rn is the MacroCommand*
{
    int failures = NULL_DEFINITION;
    const int OK = success;

    // 1. rename a .txt file
    touch->execute("old.txt");
    if (auto* f = fs->openFile("old.txt")) {
        f->write({'A','B','\n'});
        fs->closeFile(f);
    }

    if (rn->execute("old.txt new") != OK) ++failures;

    if (fs->openFile("old.txt") != nullptr) ++failures;

    if (auto* newTxt = fs->openFile("new.txt")) {
        if (newTxt->read() != std::vector<char>{'A','B','\n'}) ++failures;
        fs->closeFile(newTxt);
    } else ++failures;

    // 2. rename an .img file
    touch->execute("pic.img");
    if (auto* f = fs->openFile("pic.img")) {
        f->write({'X','X','X','X','2'});
        fs->closeFile(f);
    }

    if (rn->execute("pic.img icon") != OK) ++failures;

    if (fs->openFile("pic.img") != nullptr) ++failures;

    if (auto* icon = fs->openFile("icon.img")) {
        if (icon->read() != std::vector<char>{'X','X','X','X'}) ++failures;
        fs->closeFile(icon);
    } else ++failures;

    // 3. error path: dest already exists
    touch->execute("foo.txt");
    touch->execute("bar.txt"); // pre‑existing destination for erroring tests

    // silence stderr for this call only
    std::streambuf* oldBuf = std::cerr.rdbuf();
    std::ostringstream sink;
    std::cerr.rdbuf(sink.rdbuf());

    int rc = rn->execute("foo.txt bar");
    if (rc == OK) ++failures; // should NOT succeed

    // originals must still be present
    // originals must still be present
    auto* fooPtr = fs->openFile("foo.txt");
    auto* barPtr = fs->openFile("bar.txt");

    if (!fooPtr || !barPtr) ++failures;

    if (fooPtr) fs->closeFile(fooPtr);
    if (barPtr) fs->closeFile(barPtr);

    std::cerr.rdbuf(oldBuf); // Resource Cleanup
    return failures;
}

// Test for LSCommand
int Test::runLSTests(AbstractFileSystem* fs, TouchCommand* touch, LSCommand* ls)
{
    int failures = 0;
    const int OK = 0;

    // Create some test files with different types
    assert(touch->execute("file1.txt") == OK);
    assert(touch->execute("file2.img") == OK);
    assert(touch->execute("file3.txt") == OK);

    // Test normal ls (two-column output)
    if (ls->execute("") != OK) ++failures;

    // Test ls -m (metadata output)
    if (ls->execute("-m") != OK) ++failures;

    // Test invalid option
    if (ls->execute("-x") == OK) ++failures;

    return failures;
}

// Test for RemoveCommand
int Test::runRemoveTests(AbstractFileSystem* fs, TouchCommand* touch, RemoveCommand* rm)
{
    int failures = 0;
    const int OK = 0;

    // Create and remove a text file
    assert(touch->execute("temp.txt") == OK);
    if (rm->execute("temp.txt") != OK) ++failures;
    if (fs->openFile("temp.txt") != nullptr) ++failures;

    // Create and remove an image file
    assert(touch->execute("temp.img") == OK);
    if (rm->execute("temp.img") != OK) ++failures;

    // Try to remove non-existent file
    if (rm->execute("nonexistent.txt") == OK) ++failures;

    // Test removing an open file (should fail)
    assert(touch->execute("open.txt") == OK);
    AbstractFile* file = fs->openFile("open.txt");
    if (file && rm->execute("open.txt") == OK) ++failures;
    if (file) fs->closeFile(file);

    return failures;
}

// Test for DisplayCommand
int Test::runDisplayTests(AbstractFileSystem* fs, TouchCommand* touch, DisplayCommand* ds)
{
    int failures = 0;
    const int OK = 0;

    // Create and populate a text file
    assert(touch->execute("display.txt") == OK);
    AbstractFile* file = fs->openFile("display.txt");
    if (file) {
        file->write({'T','e','s','t'});
        fs->closeFile(file);
    }

    // Test formatted display
    if (ds->execute("display.txt") != OK) ++failures;

    // Test unformatted display (-d)
    if (ds->execute("display.txt -d") != OK) ++failures;

    // Test with non-existent file
    if (ds->execute("noexist.txt") == OK) ++failures;

    // Test with image file
    assert(touch->execute("image.img") == OK);
    file = fs->openFile("image.img");
    if (file) {
        file->write({'X','X','X','X','2'});
        fs->closeFile(file);
    }
    if (ds->execute("image.img") != OK) ++failures;
    if (ds->execute("image.img -d") != OK) ++failures;

    return failures;
}

// Test for MacroCommand functionality
int Test::runMacroTests()
{
    int failures = 0;
    const int OK = 0;

    MacroCommand macro;

    // Test macro without parsing strategy (should fail)
    if (macro.execute("test") == OK) ++failures;

    // Test macro with strategy but no commands
    RenameParsingStrategy* strategy = new RenameParsingStrategy();
    macro.setParseStrategy(strategy);
    if (macro.execute("test test") == OK) ++failures;

    delete strategy;

    return failures;
}