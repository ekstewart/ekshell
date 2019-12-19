#include "../src/base.cpp"
#include "../src/parser.cpp"

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
        //root = p->inputTree();
        root->executeCmd();
    }
	
    return 0;
}
