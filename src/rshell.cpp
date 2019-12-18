#include "../header/base.h"
#include "../header/parser.h"

#include "../src/base.cpp"
#include "parser.cpp"

using namespace std;

int main(){
    cout<<"************************************************"<<endl;
    cout<<"WELCOME TO EKSHELL"<<endl;
    cout<<"************************************************"<<endl;
	
	Base* root;
	Parser* p = new Parser();
    /*Repeating while loop to receive user input*/
    while(true)
    {
        root = read->inputTree();
        root->executeCmd();
    }
	
    return 0;
}
