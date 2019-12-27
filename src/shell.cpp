#include "../src/base.cpp"
#include "../src/parser.cpp"

using namespace std;

int main(){
    cout<<"************************************************"<<endl;
    cout<<"WELCOME TO EKSHELL"<<endl;
    cout<<"************************************************"<<endl;
	
	Base* root;
	Parser* p;
	string input;
    /*Repeating while loop to receive user input*/
    while(true)
    {
    	cout<<"$";
    	getline(cin,input);
    	cout<<"Input is "<<input<<endl;
        root = p->getTree(input);
        if(root!= nullptr){
			root->executeCmd();
		}
    }
	
    return 0;
}
