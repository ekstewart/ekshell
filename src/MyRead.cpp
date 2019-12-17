#ifndef MYREAD_CPP
#define MYREAD_CPP

#include <iostream>
#include <stack>
#include <vector>
#include "../header/MyRead.hpp"
using namespace std;

string MyRead::trimWhitespace(string input)
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
vector<string> MyRead::getTokens(string input)
{
	stack<string> quoteStack;
	stack<string> parenStack;
	vector<string> nodeList; // composed of any type of CCC
	input = trimWhitespace(input);
	
	for(int i = 0; i<input.size() ;i++){
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
			for(int j = i+1; parenStack.size()>0;j++){
				if(input[j]==')')
			}
			nodeList.emplace_back(input.substr(i,j-i+1));
			input = input.substr(j);
			i = -1;
		}
	}
	
	
}



#endif