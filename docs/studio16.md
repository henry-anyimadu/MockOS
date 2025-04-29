# Studio 16
# 1. Kelenna Eke-Okoro, Henry Anyimadu, Jonah Sachs
# 2a. Use a class with all pure virtual functions (functions with = 0), like virtual int write(...) = 0;
# 3a. This is interface inheritance since TextFile implements abstract functions from AbstractFile.
# 3b. private
# 4. Tested write(), append(), read(), getSize(), and getName(). All displayed expected behaviour.
# write(), read(), append() can be tested by viewing visual output
# getsize(), getName() can be tested and view for multiple inputs --> displayed expect results for varying name/len
# 5. Used a pointer/reference to AbstractFile to call TextFile methods polymorphically.
# We include the testing and then initialization used in main:
# std::unique_ptr<AbstractFile> file = std::make_unique<TextFile>("Textfile");
# const string literal2 = "Testing the Polymorphism!\n";
# const vector<char> data3(literal2.begin(), literal2.end());
# file->write(data3);
# file->read();
# //testing append for the polymorphism
# const string append2 = "Testing the Polymorphism Append.\n";
# const vector<char> data4(append2.begin(), append2.end());
# file->append(data4);
# 6. Tested the code using the unit tests and passed all so far
