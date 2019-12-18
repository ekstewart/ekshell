#ifndef BASE_CPP
#define BASE_CPP

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include "../header/base.h"
using namespace std;


/************** CONNECTOR FUNCTIONS *****************/
Connect::Connect(Base* left, Base* right)
{
    addLeft(left);
    addRight(right);
}

void Connect::addLeft(Base *left)
{
    this->left = left;
}
void Connect::addRight(Base* right)
{
    this->right = right;
}


/*************** COMMAND FUNCTIONS ***********************/
string Command::trimWhitespace(string input)
{
	size_t len = input.length();
	int st = 0;
	while ((st < len) && (input[st] <= ' ')) {
		st++;
	}
	while ((st < len) && (input[len - 1] <= ' ')) {
		len--;
	}
	return ((st > 0) || (len < input.length())) ? input.substr(st, len-st) : input;
}

void Command::parseToStringVector(string cmdString)
{
	vector<string> parsedCmdList;
	cmdString = trimWhitespace(cmdString);
	
	if(cmdString.size() == 0 || cmdString.find(" ")==string::npos) // if size is 0, then cmdString is an empty string. Or if ==npos, there is only one word,
	{
		parsedCmdList.emplace_back(cmdString);
	}
	else // Multiple tokens within command
	{
		while(cmdString.size()>0)
		{
			for(int i = 0;i<cmdString.size();i++)
			{
				if(cmdString[i]=='"') // Add substring from quotation to quotation
				{
					int nextQuote = cmdString.find("\"",1) + 1;
					parsedCmdList.emplace_back(cmdString.substr(i+1,nextQuote-2));
					cmdString = cmdString.substr(nextQuote);
					cmdString = trimWhitespace(cmdString);
					break;
				}
				else if(cmdString[i]==' ')
				{
					parsedCmdList.emplace_back(cmdString.substr(0,i));
					cmdString = cmdString.substr(i);
					cmdString = trimWhitespace(cmdString);
					break;
				}
				else if(cmdString.find(" ")==string::npos)
				{
					parsedCmdList.emplace_back(cmdString);
					cmdString = "";
					break;
				}
			}
		}
	}
	parsedCmdList.emplace_back("");
	
	this->parsedCmdList = parsedCmdList;
}

void Command::convertToCStringVector()
{
	vector<char*> vec(parsedCmdList.size()); // Create an intermediary vector(since you cant just define vector<char*> args again)
	this->args = vec;
	for(size_t i = 0;i < parsedCmdList.size();i++){
		args[i] = &parsedCmdList[i][0];
	}
	this->args.at(this->args.size()-1) = nullptr;// Set the last index equal to null
}

void Command::callTestCommand()
{
	// index[1] will be the flag
	// index[2] will be the file path or dir path
	// index[3] will be the ']' token, which we may assume exists within this function
	struct stat buf;
	string flag = parsedCmdList.at(1);
	string filePath = parsedCmdList.at(2);
	
	if(filePath == "]"){//if no flag is entered and the ordering is messed up
		filePath = flag;
		flag = "-e";
	}
	
	if(flag == "-e")
	{
		if(stat(filePath.c_str(), &buf) == 0)
		{
			cout<<"(True)"<<endl;
			this->runStatus = true;
		}
		else
		{
			cout<<"(False)"<<endl;
			this->runStatus = false;
		}
	}
	else if(flag == "-f")
	{
		if(stat(filePath.c_str(), &buf) == 0)
		{
			if(S_ISREG(buf.st_mode))
			{
				cout<<"(True)"<<endl;
				this->runStatus = true;
			}else{
				cout<<"(False)"<<endl;
				this->runStatus = false;
			}
		}
		else
		{
			cout<<"(False)"<<endl;
			this->runStatus = false;
		}
	}
	else if(flag == "-d")
	{
		if(stat(filePath.c_str(), &buf) == 0)
		{
			if(S_ISDIR(buf.st_mode))
			{
				cout<<"(True)"<<endl;
				this->runStatus = true;
			}else{
				cout<<"(False)"<<endl;
				this->runStatus = false;
			}
		}
		else
		{
			cout<<"(False)"<<endl;
			this->runStatus = false;
		}
	}
	else{
		cout<<"INVALID ARG FOUND WITH TEST [] COMMAND"<<endl;
	}
}

Command::Command(string argList)
{
	runStatus = true;
	parseToStringVector(argList);
	convertToCStringVector();
}

bool Command::executeCmd()
{
	if(this->parsedCmdList.at(0) == "exit")
	{
		cout<<"Exiting..."<<endl;
		exit(0);
	}
	if(this->parsedCmdList.at(0)[0]=='[')// if child process is executing the test command
	{
		if(this->parsedCmdList.at(this->parsedCmdList.size()-2)=="]")
		{
			// CALL FUNCTION HERE
			callTestCommand();
			return this->runStatus;
		}
		this->runStatus = false;
		cout<< "NO CLOSING BRACKET FOUND\nINVALID USAGE OF []"<<endl;
		return this->runStatus;
	}
	
	pid_t pid = fork();
	int waitStatus;
	
	if(pid == 0) // For child process
	{
		if(execvp(this->args[0],this->args.data())==-1)
		{
			this->runStatus = false;
			perror("execvp ran into an error");
			exit(1);
		}
	}
	if(pid > 0) // For parent process
	{
		if(waitpid(pid, &waitStatus, 0)==-1)
		{
			perror("waitpid received an error");
		}
		if(WEXITSTATUS(waitStatus) != 0)
		{
			this->runStatus = false;
		}
	}
	return this->runStatus;
}


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
DecoratorBase::DecoratorBase(Base *child, string fileName)
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
void DecoratorBase::addChild(Base* child)
{
    this->decoChild = child;
}
Base* DecoratorBase::getChild()
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
