#ifndef COMMAND_CPP
#define COMMAND_CPP

#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <vector>
#include "../header/CCC.h"
using namespace std;

/***************PRIVATE FUNCTIONS***********************/
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

/**************PUBLIC FUNCTIONS*************************/
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


#endif
