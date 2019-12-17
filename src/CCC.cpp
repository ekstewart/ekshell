#ifndef CCC_CPP
#define CCC_CPP

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include "../header/CCC.h"

using namespace std;


/************** CONNECTOR FUNCTIONS *****************/
Connect::Connect(CCC* left, CCC* right)
{
    addLeft(left);
    addRight(right);
}

void Connect::addLeft(CCC *left)
{
    this->left = left;
}
void Connect::addRight(CCC* right)
{
    this->right = right;
}
//getLeft and getRight functions created in CCC.h file

/************** AND FUNCTIONS ***********************/
bool And::executeCmd()
{
    if(left->executeCmd()){
        return right->executeCmd();
    }
    else{
        return false;
    }
}

/************** OR FUNCTIONS ************************/
bool Or::executeCmd()
{
    if(!left->executeCmd()){
        return right->executeCmd();
    }
    else{
        return true;
    }
}
/************** SEMI FUNCTIONS *****************/
bool Semi::executeCmd()
{
    left->executeCmd();
    return right->executeCmd();
}
/************** PIPE FUNCTIONS *****************/
bool PipeCon::executeCmd()
{
    int pipefd[2];
    int stdInLocation;
    int stdOutLocation;
    int waitStatus;
    pid_t cpid;
    
    if(pipe(pipefd)==-1){
        perror("Error in pipe");
        return false;
    }
    cpid = fork();
	
	//Store StdOut, replace with WR end of pipe(pipefd[1]), call left child's executeCmd, close pipe end, restore stdOut
    if(cpid == 0){// Write end of pipe for child
    	close(pipefd[0]);
    	stdOutLocation = dup(1);
    	dup2(pipefd[1],1);
    	left->executeCmd();
    	close(pipefd[1]);
    	dup2(stdOutLocation,1);
    	exit(0);
    }
	
	if(cpid > 0){ // For parent process
		if(waitpid(cpid, &waitStatus, 0)==-1){
			perror("waitpid received an error");
		}else{
			//Store StdIn, replace with RE end of pipe(pipefd[0]), call right child's executeCmd, close pipe end, restore stdIn
			close(pipefd[1]);
			stdInLocation = dup(0);
			dup2(pipefd[0],0);
			runStatus = right->executeCmd();
			close(pipefd[0]);
			dup2(stdInLocation,0);
		}
		if(WEXITSTATUS(waitStatus) != 0){
			this->runStatus = false;
		}
	}
	return runStatus;
}

/************** DECORATORBASE FUNCTIONS *****************/
DecoratorBase::DecoratorBase(CCC *child, string fileName)
{
	setFile(fileName);
	addChild(child);
}
void DecoratorBase::setFile(string fileName)
{
    this->fileName = fileName;
}
string DecoratorBase::getFileName()
{
    return this->fileName;
}
void DecoratorBase::addChild(CCC* child)
{
    this->decoChild = child;
}
CCC* DecoratorBase::getChild()
{
    return this->decoChild;
}

/************** OUTPUTOVERWRITE FUNCTIONS *****************/
// Store stdOut, replace it, run command, restore stdOut
bool OutputOverwrite::executeCmd()
{
    int fdOut = open(getFileName().c_str(), O_WRONLY| O_TRUNC | O_CREAT,  S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    int stdOutLocation = dup(1);
	dup2(fdOut,1);
    this->runStatus = decoChild->executeCmd();
    dup2(stdOutLocation,1);
	
	return runStatus;
}


/************** OUTPUTAPPEND FUNCTIONS *****************/
// Store stdOut, replace it, run command, restore stdOut
bool OutputAppend::executeCmd()
{
    int fdOut = open(getFileName().c_str(), O_WRONLY| O_APPEND | O_CREAT,  S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    int stdOutLocation = dup(1);
    dup2(fdOut,1);
    this->runStatus = decoChild->executeCmd();
	dup2(stdOutLocation,1);
	
	return runStatus;
}


/************** INPUTREDIRECT FUNCTIONS *****************/
// Store stdIn, replace it, run command, restore stdIn
bool InputRedirect::executeCmd()
{
	struct stat buf;
	if(stat(fileName.c_str(), &buf) == 0)
	{
		if(S_ISREG(buf.st_mode))
		{
			int fdIn = open(getFileName().c_str(), O_RDONLY);
			int stdInLocation = dup(0);
			dup2(fdIn,0);
			this->runStatus = decoChild->executeCmd();
			dup2(stdInLocation,0);
			return runStatus;
		}else{
			return false;
		}
	}
	else
	{
		return false;
	}
 
}


#endif
