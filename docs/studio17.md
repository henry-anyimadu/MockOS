# Studio 17
1. Kelenna Eke-Okoro, Henry Anyimadu, Jonah Sachs

2.  Tested with valid and invalid inputs:
Valid: {'X',' ','X',' ','X',' ','X',' ','X','3'} → displayed 3x3 grid
Invalid: wrong size or character → returned error, size = 0, cleared contents
Description of further tests:
-->Add file in for both text and image file and check the resulting error int (see test cases above)
-->Create file for both text and image file and check error int
-->Tried and unrecognized extension to test that failure case and saw expected results
-->Also testing open(), read(), write(), and close() via the same mechanism applied above. saw expected results
--> through outputted error_types

2e.  Should be private, since it's an internal utility not needed outside the class. Protected should be reserved for extensions
Private allows us to maximize encapsulation without increasing the coverage of the API

3. interfaces promote flexibility, future file system types can be added w/o changing client code.  simplifies maintenance and supports polymorphism.

4 - You’d need to edit the createFile method in SimpleFileSystem to check for a new file extension then instantiate a MusicFile. This creates a dependency that we’ll later remove with a dedicated file factory.
