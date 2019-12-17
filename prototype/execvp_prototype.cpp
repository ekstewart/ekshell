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
