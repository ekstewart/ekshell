### *Project derived from UCR Software Construction course*

# EKShell
## Introduction:
This is a relatively basic shell that is able to run simple executables and can be a stand in for other (way more advanced and useful) shells on the market. 
**To run this shell you must be on a linux shell and have either cmake or g++ installed**
## Perform the following commands in your standard shell:
- First clone the repository
```git --recursive clone <git repo link>```
- Then navigate into the repo's directory
```cd ekshell```
- Compile the files using the CMakeList.txt and one of the following commands
```cmake . && make``` or ```cmake3 . && make```
- If the `make` command runs successfully, you should generate the `shell` binary file in your ekshell/ directory. Go ahead and run the file with: 
```./shell```

## Specifications:
Within the design specifications of this project, I created a command shell called rshell using C++.
The command shell completes/seeks to complete the following tasks. 
- Reading commands and connectors from standard input
- Execute some appropriate commands using fork, execvp, and waitpid.
- Represent commands and operators using a composite pattern (Structure using recursive composition.)
- Allow for input redirection and piping
- Allow for usage of the 'cd' command

## Directories:
* **googletest**: Submodule that contains a copy of Google's testing framework.
* **header**: Collection of all header files (files listing the headers for each class's member functions and variables.)
* **images**: Images used/to be used in README
* **prototype**: Small individual files testing out different linux functionalities and calls
* **src**: Collection of all implementation files ( .cpp files containing function definitions)
* **unit_tests**: Various files containing unit tests for different functionalities

## Classes:
* Base: abstract class which implements specific behaviors with its child components.
* Command: Acts as the leaf class in composite structure
* Connector: Acts as the composite in composite structure, containing lower Commands within it
* Command: Class which processes individual commands with execvp and communicates an exit status
* And: Class which acts as the && connector in a tree
* Or: Class which acts as the || connector in a tree
* Semi: Class which acts as the ; connector in a tree
* PipeCon: Class which acts as the | connector in a tree, uses pipe() function to redirect stdInput and stdOutput
* DecoratorBase: Base class which extends the Base class and is the super for the OutputOverwrite, OutputAppend, and InputRedirect classes
* OutputOverwrite: Decorator object that changes the output direction of its child node and writes to a file 
* OutputAppend: Decorator object that changes the output direction of its child node and appends to a file
* InputRedirect: Decorator object that changes the input direction of its child node and takes in input from a file
