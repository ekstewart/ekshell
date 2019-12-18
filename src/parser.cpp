#ifndef PARSER_CPP
#define PARSER_CPP

#include <iostream>
#include <stack>
#include <vector>
#include "../header/parser.h"
using namespace std;

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
		else if(input[i]=='#'){
			input = "";
			i = -1;//reset index variable after truncating input string
		}
		else if(input[i]=='('){
			parenStack.push("(");
			int j;
			for(j = i+1; parenStack.size()>0;j++){
				if(input[j]==')')
					parenStack.pop();
				else if(input[j]=='#')
					throw string inv("Incomplete parentheses found!");
			}
			nodeList.emplace_back(input.substr(i,j-i+1));
			input = input.substr(j);
			i = -1;//reset index variable after truncating input string
		}
		else if(input[i]=='&' && input[i+1]=='&'){//if next characters in a sequence are "&&" connector
			
		}
		else if(input[i]=='|'){//if next characters are a pipe or "||" connector
		
		}
		else if(input[i]==';'){//if next character is a semi colon connector
		
		}
	}
	
	
}



#endif