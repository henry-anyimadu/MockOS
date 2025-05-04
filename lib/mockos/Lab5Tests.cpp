//
// Created by Jonah Sachs on 5/3/25.
//


#include <cassert>
#include <iostream>
#include <sstream>

#include "mockos/TextFile.h"
#include "mockos/Lab5Tests.h"
#include "mockos/PasswordProxy.h"


int Test::runCopyTests(AbstractFileSystem* fs,
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
int Test::runTouchTests(AbstractFileSystem* fs,
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


//--------------------------------------------------------------
//  Helper: automated tests for Rename (rn) MacroCommand
//--------------------------------------------------------------
int Test::runRenameTests(AbstractFileSystem* fs,
                   TouchCommand*       touch,
                   AbstractCommand*    rn)   // rn is the MacroCommand*
{
    int failures = 0;
    const int OK = success;          // 0 in your enum

    //---------------- 1. rename a .txt file -----------------
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

    //---------------- 2. rename an .img file ----------------
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

    //---------------- 3. error path: dest already exists ----
    touch->execute("foo.txt");
    touch->execute("bar.txt");            // pre‑existing destination for erroring tests

    // ---- silence stderr for this call only ----
    std::streambuf* oldBuf = std::cerr.rdbuf();
    std::ostringstream sink;
    std::cerr.rdbuf(sink.rdbuf());


    int rc = rn->execute("foo.txt bar");
    if (rc == OK) ++failures;             // should NOT succeed

    // originals must still be present
    // originals must still be present
    auto* fooPtr = fs->openFile("foo.txt");
    auto* barPtr = fs->openFile("bar.txt");

    if (!fooPtr || !barPtr) ++failures;

    if (fooPtr) fs->closeFile(fooPtr);
    if (barPtr) fs->closeFile(barPtr);

    return failures;
}



