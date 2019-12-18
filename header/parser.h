#ifndef MYREAD_HPP
#define MYREAD_HPP
/**
 * @author Evan Stewart
 */
#include <string>
#include <vector>
#include <stack>
using namespace std;

class MyRead{
	private:
		string trimWhitespace(string input);
		vector<string> getTokens(string input);
		
	
	public:
		MyRead();
		CCC* getTree(string input);
};



#endif
