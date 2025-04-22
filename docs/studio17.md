# Studio 17
Kelenna Eke-Okoro, Henry Anyimadu, Jonah Sachs
2 - Tested with valid and invalid inputs:
Valid: {'X',' ','X',' ','X',' ','X',' ','X','3'} → displayed 3x3 grid
Invalid: wrong size or character → returned error, size = 0, cleared contents

2e - Should be private, since it's an internal utility not needed outside the class.

3 -  interfaces promote flexibility, future file system types can be added w/o changing client code.  simplifies maintenance and supports polymorphism.

4 - You’d need to edit the createFile method in SimpleFileSystem to check for a new file extension then instantiate a MusicFile. This creates a dependency that we’ll later remove with a dedicated file factory.
