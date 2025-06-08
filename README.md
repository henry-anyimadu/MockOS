# Mock Operating System in the Command Line - Built with C++

Names: Jonah Sachs, Henry Anyimadu, Kelenna Eke-Okoro

Lab #5 for CSE 332: Intro to Object-Oriented Programming in C++

Division of work:
- For the studios we worked collaboratively, scheduling meetings in person and divvying up work asynchronously.
- For the lab we split work based on availability. With final exams and projects, we focused on _when_ team members could
work, instead of what they could work on.
- We all collaborated on studio 16 in person. We then worked async, with Jonah taking on the next 2 studios, and Henry
finishing the studio portion of the lab from there.
- For Lab 5, all of us worked together to find and squash bugs as we found them while creating our MockOS commands.

## Commands Implemented
1. **LSCommand** (`ls`)
    - Lists all files in the filesystem
    - Default: Two-column format with filenames
    - `-m` option: One file per line with metadata (name, type, size)
    - Properly formats output with padding for alignment

2. **RemoveCommand** (`rm`)
    - Removes a specified file from the filesystem
    - Fails if file doesn't exist or is currently open
    - Returns appropriate error codes

3. **TouchCommand** (`touch`)
    - Creates new files (text or image)
    - `-p` option: Creates password-protected files using PasswordProxy
    - Prompts for password when creating protected files
    - Enhanced error handling for invalid extensions

4. **CatCommand** (`cat`) ^_^
    - Edits file contents with write/append modes
    - Default: Overwrites file contents
    - `-a` option: Appends to existing content
    - Editor commands: `:wq` (save & quit), `:q` (quit without saving)
    - Handles image and text files differently (no trailing newlines for images)

5. **DisplayCommand** (`ds`)
    - Shows file contents
    - Default: Uses appropriate visitor for formatted display
    - `-d` option: Raw data output without formatting
    - Works with both text and image files

6. **CopyCommand** (`cp`)
    - Copies existing files using the prototype pattern
    - Syntax: `cp <source> <destination_base_name>`
    - Automatically adds correct extension to destination
    - Preserves file type and content
    - Handles password-protected file copying

7. **RenameMacro** (`rn`)
    - Renames files by copying to new name and removing original
    - Uses RenameParsingStrategy to process arguments
    - Built from CopyCommand and RemoveCommand
    - Handles error cases (source doesn't exist, destination exists)

8. **TouchEditMacro** (`te`)
    - Creates a file and immediately opens it in cat editor
    - Custom macro implementation chosen for efficiency
    - Uses TouchEditParsingStrategy for argument parsing
    - Combines TouchCommand and CatCommand functionality

## Design Decisions

- All commands inherit from AbstractCommand
- Commands execute on an AbstractFileSystem pointer
- Every operation has error codes + error messages

## Testing
- Unit tests for all command functionalities
- Edge case testing (empty files, invalid extensions, etc.)
- Macro command integration testing
- Password-protected file operations
- Memory management verification

### Copy
- Copying Text file
- Copying Image file
- Copying password-protected file

### Touch
- Creating a Text file
- Creating an Image file
- Attempting to create a duplicate file
- Creating a file with an unknown extension
- Creating a file with password protection

### Rename
- Renaming a text file
- Renaming an image file
- Renaming to an existing file

### List
- Test 2 column (base case) LS
- Test metadata (-m) output
- Test an invalid flag

### Remove
- Remove a text file
- Remove an img file
- Attempt to remove a file that doesn't exist

### Display
- Display a text file
- Test properly/improperly formatted command
- Display an image file

## Notable Errors (all fixed)
When we began lab 5, we ran into multiple errors regarding methods created in the studios, mainly surrounding
password protection, the touch command, and the command line.

### Password Protection
- Error: Password-protected files were being manipulated without asking for the password
- We were able to alter the implementation of both PasswordProxy and TouchCommand to require password protection.
- TouchCommand was creating 2 files, one password protected and one not, resulting in security issues as well as double deletion.

### Touch Command
- Error: Touch command wasn't recognizing when an input ended in "-p"
- Researched potential fixes and found parser functionality in istringstream
- Went from iterating through the string manually, to using parser for the "-p" flag
- Was then able to use this newfound knowledge in implementing the rest of our commands

### Command Prompt
- Errors: Kept getting "Command Failed to Execute" whenever any other command was run
- We used a command that printed out the exact error type we were getting from the command line.
We were then able to use this to discern what our errors were with the command line.
- Error lied in our input buffer handling, used 'getline' instead of cin to solve.


