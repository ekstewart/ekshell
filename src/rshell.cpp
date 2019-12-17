#include "../header/CCC.h"
#include "../header/read.h"
#include "../header/reference.h"
//#include "../header/command.h"

#include "../src/CCC.cpp"
#include "../src/read.cpp"
#include "../src/reference.cpp"
#include "../src/command.cpp"

using namespace std;

int main(){
    cout<<"************************************************"<<endl;
    cout<<"WELCOME TO PROJECT_FAILED_SUCCESSFULLY'S RSHELL"<<endl;
    cout<<"************************************************"<<endl;
	
	CCC* root;
	Read* read = new Read();
    /*Repeating while loop to receive user input*/
    while(true)
    {
        root = read->inputTree();
        root->executeCmd();
    }
	
    return 0;
}
