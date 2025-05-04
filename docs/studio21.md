# Studio 21
Kelenna Eke-Okoro, Henry Anyimadu, Jonah Sachs
Part 2b:  To ensure the correct derived class destructor is called when deleting via a base class pointer, preventing resource leaks.

Part 4 (middle): Dependency injection decouples CommandPrompt from concrete file system/factory implementations. also it depends only on interfaces for easy configuration with different concrete classes w/o changing the CommandPrompt code.

Part 4 (end): Ran CommandPrompt. Tested help, help touch. Executed touch myFile.txt (tested success and failure on duplicate). Typed q to quit. Verified file creation afterwards using fileSystem->openFile("myFile.txt").