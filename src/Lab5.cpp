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
#include "mockos/MacroCommand.h"
#include "mockos/RenameParsingStrategy.h"
#include "mockos/RenameMacro.h"
#include "mockos/Lab5Tests.h"
#include "mockos/TouchEditMacro.h"
#include "mockos/TouchEditParsingStrategy.h"


/**
 *
 * Main file for Lab5
 *
 */
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

    //create rename
    auto* renameCmd = new RenameMacro();
    renameCmd->addCommand(cpcommand);
    renameCmd->addCommand(removeCommand);
    RenameParsingStrategy* rnParse = new RenameParsingStrategy();
    renameCmd->setParseStrategy(rnParse);



    //create touch and edit (te)
    auto* teMacro = new TouchEditMacro();
    teMacro->addCommand(touchCommand);
    teMacro->addCommand(catcommand);
    TouchEditParsingStrategy* teParse = new TouchEditParsingStrategy();
    teMacro->setParseStrategy(teParse);



    //Add the rn command through the MacroCommands interface
    cp->addCommand("rn", renameCmd);



    //add the te (touch and edit) command through the MacroCommands interface
    cp->addCommand("te", teMacro);

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

    if (int fails = Test::runCopyTests(fileSystem, touchCommand, cpcommand))
        std::cout << "[CopyCommand tests] FAILED: " << fails << '\n';
    else
        std::cout << "[CopyCommand tests] all passed\n";


    if (int fails = Test::runTouchTests(fileSystem, touchCommand))
        std::cout << "[TouchCommand tests] FAILED: " << fails << '\n';
    else
        std::cout << "[TouchCommand tests] all passed\n";


    if (int fails = Test::runRenameTests(fileSystem, touchCommand, renameCmd))
        std::cout << "[RenameCommand tests] FAILED: " << fails << '\n';
    else
        std::cout << "[RenameCommand tests] all passed\n";


    // Run the command prompt
    int cp_r = cp->run();

    // Clean up
    delete cp;
    delete fileSystem;
    delete fileFactory;

    return cp_r;
}