# CS 100 Programming Project
## Fall, 2019: 
### Evan Stewart,	ID:862155844
### Kevin Chen,     ID:861298653

## Introduction:
Within the design specifications of this project, we created a command shell called rshell using C++.
The command shell completes some following tasks. 
These task includes: printing a command prompt; reading commands and connectors from 
standard input; execute some appropriate commands like fork, execvp, and waitpid.
When representing commands and operators we implemented a composite pattern.
Within navigating the command shell there are some directories.
Directory src/ contains all the source (.cc/.cpp) files for the project.
Directory header/ contains some required header files.
Directory unit_test/ contains all the unit tests created from the Google Unit Test framework.
Directory integration_test/ contains all the unit tests written from bash.
As a recommendation for bash integration tests, IO redirection is used instead of automated validation.
Within the root directory we included CMakeLists.txt to target two specifications.
rshell: build the main executable.
test: run the unit test created from the Google Unit Test framework.
From this project a command shell was born.

## Diagram:
![OMT Diagram](/images/LucidOMTDiagram.jpeg)

## Classes:
* CCC: abstract class which implements specific behaviors with its child components.
* Command: Acts as the leaf class in composite structure
* Connect: Acts as the composite in composite structure, containing lower Commands within it
* Read: Class which receives user input and constructs a tree of commands based on various connectors
* Reference: Stores and detects all inputs that need to be modified by the read class
* Command: Class which processes individual commands with execvp and communicates an exit status
* And: Class which acts as the && connector in a tree
* Or: Class which acts as the || connector in a tree
* Semi: Class which acts as the ; connector in a tree
* PipeCon: Class which acts as the | connector in a tree, uses pipe() function to redirect stdInput and stdOutput
* DecoratorBase: Base class which extends the CCC class and is the super for the OutputOverwrite, OutputAppend, and InputRedirect classes
* OutputOverwrite: Decorator object that changes the output direction of its child node and writes to a file 
* OutputAppend: Decorator object that changes the output direction of its child node and appends to a file
* InputRedirect: Decorator object that changes the input direction of its child node and takes in input from a file


* fork(): Creates a new process that runs concurrently with the parent process, returns int 0 if the process is a child and some int greater than 0 if the process is the parent
* waitpid():Typically used in the parent process. Called for the parent process to wait for the child process to be fully executed and then terminated. 
* execvp(): Takes in some char* arguments along with a char* [ ] arguments list to run an executable program.

## Prototypes/Research:
```c++
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

int main(){
	//char* to char[]
	//0'th index should be the executable
	//1'th index should be any additional arguments
	//2'nd index should be NULL or nullptr depending on the version of C++
	char* args[3];
	string conCatCmd = "cat";
	string fileName = "names.txt";

	//Populate the arguments array
	args[0] = (char*)conCatCmd.c_str();
	args[1] = (char*)fileName.c_str();
	args[2] = nullptr;

	execvp(args[0],args);
		
	return 0;
}
```
