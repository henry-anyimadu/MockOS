# Studio 16

# 2a. Use a class with all pure virtual functions (functions with = 0), like virtual int write(...) = 0;
# 3a. This is interface inheritance since TextFile implements abstract functions from AbstractFile.
# 3b. private
# 4. Tested write(), append(), read(), getSize(), and getName(). All behaved as expected.

# 5. Used a pointer/reference to AbstractFile to call TextFile methods polymorphically.
# AbstractFile* file = new TextFile("hello");
# file->write({'H','i'});
# file->append({'!'});
# file->read();
# delete file;
