#ifndef PARSER_CPP
#define PARSER_CPP

#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include "../header/parser.h"
using namespace std;

Parser::Parser()
{
	conMap.insert(pair<string,int>("&&",0));
	conMap.insert(pair<string,int>("||",1));
	conMap.insert(pair<string,int>(";",2));
	conMap.insert(pair<string,int>("|",3));
	conMap.insert(pair<string,int>(">",4));
	conMap.insert(pair<string,int>(">>",5));
	conMap.insert(pair<string,int>("<",6));
}

string Parser::trimWhitespace(string input)
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
vector<string> Parser::getTokens(string input)
{
	stack<string> quoteStack;
	stack<string> parenStack;
	vector<string> nodeList; // composed of any type of Base pointer
	input = trimWhitespace(input);
	
	for(int i = 0; i<input.size() ;i++){//echo h
		if(quoteStack.size()>0 && input[i]!='\"'){
			continue;
		}
		if(input[i]=='\"'){
			if(quoteStack.size()>0)
				quoteStack.pop();
			else
				quoteStack.push("\"");
		}
		else if(input[i]=='('){
			parenStack.push("(");
			int j;
			for(j = i+1; parenStack.size()>0;j++){
				if(input[j]==')')
					parenStack.pop();
				else if(input[j]=='(')
					parenStack.push("(");
				else if(input[j]=='#'){
				    string inv = "Incomplete parentheses found!";
				    throw inv;
				}
			}
			nodeList.emplace_back(input.substr(i,j-i));
			input = trimWhitespace(input.substr(j));
			i = -1;//reset index variable after truncating input string
		}
		else if((input[i]=='&' && input[i+1]=='&')||
				(input[i]=='|' && input[i+1]=='|')||
				(input[i]=='>' && input[i+1]=='>')){//if next characters in a sequence are "&&" connector or "||" connector
			if(trimWhitespace(input.substr(0,i)).size()>0){
				nodeList.emplace_back(trimWhitespace(input.substr(0,i)));
			}
			nodeList.emplace_back(input.substr(i,2));
			input = trimWhitespace(input.substr(i+2));
			i = -1;
		}
		else if(input[i]=='|' || input[i]==';' || input[i]=='>' || input[i]=='<'){//if next characters are a pipe connector
			if(trimWhitespace(input.substr(0,i)).size()>0){
				nodeList.emplace_back(trimWhitespace(input.substr(0,i)));
			}
			nodeList.emplace_back(input.substr(i,1));
			input = trimWhitespace(input.substr(i+1));
			i = -1;
		}
		else if(input[i]=='#'){
			nodeList.emplace_back(input.substr(0,i));
			input = "";
			i = -1;//reset index variable after truncating input string
		}
		else if(i==input.size()-1){// on last iteration, add remaining string into token vector
			nodeList.emplace_back(input.substr(0));
			input = "";
			i = -1;//reset index variable after truncating input string
		}
	}
	return nodeList;
}
Base* Parser::getTree(string input)
{
	Base* ptrLeft, ptrRight;
	Base* root;
	vector<string> vector = getTokens(input);
	stack<Base*> cmdStack;
	stack<string> conStack;
	
	/*Commence Shunting yard algorithm to create tree
	 * using vector of command/connector tokens*/
	for(int i = 0; i<vector.size();i++){//tokens can be paren'd, commands, connectors, file paths
		if(vector.at(i)[0]=='('){//if parentheses node
		
		} else if(conMap.find(vector.at(i))!=conMap.end()){//if a connector
		
		} else{//if a single command
		
		}
		if(cmdStack.size()>1){
			string cmdRight = cmdStack.pop();
			string cmdLeft = cmdStack.pop();
		}
	}
}



#endif
