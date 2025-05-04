# Studio 19
Kelenna Eke-Okoro, Henry Anyimadu, Jonah Sachs
Part 2c: Created TextFile, wrote initial data. Called read() to get vector<char>, modified the vector locally. Called write() with the modified vector to update the file.

Part 3c: 1. Client calls file->accept(visitor). 2. The file's accept method calls visitor->visit_FileType(this).

Part 4a: Delegation is passing responsibility. Visitor uses delegation: file objects delegate operations (like display) to visitor objects via the accept method, keeping the file interface clean.

Part 5: Adding a new file type requires modifying the visitor interface and all concrete visitors. Bad idea if the file type hierarchy changes often.