### Project derived from UCR Software Construction course

#EKShell
## Introduction:
Within the design specifications of this project, I created a command shell called rshell using C++.
The command shell completes/seeks to complete the following tasks. 
- Reading commands and connectors from standard input
- Execute some appropriate commands using fork, execvp, and waitpid.
- Represent commands and operators using a composite pattern (Structure using recursive composition.)
- Allow for input redirection and piping
- Allow for usage of the 'cd' command

Within navigating the command shell there are some directories.
Directory src/ contains all the source (.h/.cpp) files for the project.
Directory header/ contains header
Directory unit_test/ contains all the unit tests created from the Google Unit Test framework.
Directory integration_test/ contains all the unit tests written from bash.

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
