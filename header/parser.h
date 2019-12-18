#ifndef PARSER_H
#define PARSER_H
/**
 * @author Evan Stewart
 */
#include <string>
#include <vector>
#include <stack>
using namespace std;

class Parser{
	private:
		string trimWhitespace(string input);
		vector<string> getTokens(string input);
		
	
	public:
		Parser();
		Base* getTree(string input);
};



#endif
