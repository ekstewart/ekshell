#ifndef READ_H
#define READ_H

#include <stack>
#include <vector>
#include "base.h"
#include "reference.h"

class Read {
    private:
        Connect* croot; //Stores the root of the current input tree
        DecoratorBase* droot; //Used if the root of the current tree is a decorator
        Command* root;
        std::vector<CCC*> v; //Stores all the nodes to be deleted later

        bool invalidRoot();
        void setTop(Connect* temp);//Sets the root to connect
        void setTop(DecoratorBase* temp);//Sets the root to decorator
        void setTop(Command* temp);
        CCC* getTop();
        int top(); //Return 0 if null, 1 if connect, 2 if decorator, 3 if leaf
        int top(CCC* temp);
        Command* makeLeaf(std::string & total);
        void addLeaf(std::string & total);
        void addConnector(Connect* c, std::string & total);
        void addTree(CCC* c);
        
        void addDecor(DecoratorBase* d, std::string & split, std::stringstream & ss, const int cur2);
        
        void addCommand(std::string & total); //Makes a new command node with a string and empty the string
        
        void removeTree(); //Recursive function to remove an entire tree
        void makeTree(std::string input); //Makes a tree given an input string
	    std::string splitInput(std::string & input, const int type, const int pos, const bool quote); //Takes a word and splits it if it contains multiple connectors or commands
	    void testEnd(std::string & total, bool & test); //Adds the ending bracket to test command
        void checkBrackets(std::stack<Connect*> sub, bool test2); //Checks if brackets is not closed
	    bool justSpace(std::string input); //Checks if the input is only a space or empty
    public:
        Read() : croot(0), droot(0), root(0) {}
        ~Read() {removeTree(); } //Empties the current tree when this gets deconstructed
        CCC* inputTree(); //Gets user input and return tree in root
	    CCC* TESTINGinputTree(std::string input); //Alternate function only for unit tests
};

#endif
