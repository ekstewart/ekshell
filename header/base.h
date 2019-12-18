#ifndef BASE_H
#define BASE_H

#include <string>
#include <vector>

using namespace std;

class Base {
	protected:
		bool runStatus;
    public:
        Base(){} //Constructor
        virtual bool executeCmd() = 0;
        
}; //Base for composite pattern

class Command: public Base{
	private:
		vector<string> parsedCmdList;
		vector<char*> args;
		
		string trimWhitespace(string input); // Helper function to clean up leading and trailing whitespace in a string
		void parseToStringVector(string cmdString); // Helper function to convert a string to a vector<string>
													// With the first index[] being the executable and the following being arguments
		void convertToCStringVector(); // Helper function to convert the vector<string> to vector<char*>
		void callTestCommand(); // Helper function that executes 'test' or [<command>] functionality
	public:
		Command(string argList); // Constructor, expects entire command string as parameter
		virtual bool executeCmd(); // Function that calls execvp and returns exit status. TRUE if exited, FALSE if didnt exit correctly
		
		/*ONLY FOR TESTING*/
		inline vector<string> getParsedCmdList(){return parsedCmdList;}
};

class Connect : public Base {
	protected:
		Base* left; //Left child
		Base* right; //Right child
    public:
        Connect(Base* left, Base* right);
		Base* getLeft() {return left; }
		Base* getRight() {return right; }
		void addLeft(Base* left);
		void addRight(Base* right);

		virtual bool executeCmd() = 0;
}; //Connect class is for holding children and other connectors

class And : public Connect{
	public:
		And(Base* left, Base* right):Connect(left,right){}
		virtual bool executeCmd();
};
class Or : public Connect{
	public:
		Or(Base* left, Base* right):Connect(left,right){}
		virtual bool executeCmd();
};
class Semi : public Connect{
	public:
		Semi(Base* left, Base* right):Connect(left,right){}
		virtual bool executeCmd();
};

class PipeCon : public Connect{
	public:
		PipeCon(Base* left, Base* right):Connect(left,right){}
		virtual bool executeCmd();//Should open pipe, call executeCmd() on children, then close pipe ends
};

class DecoratorBase : public Base{
	protected:
		Base* decoChild;
		string fileName;
	public:
		DecoratorBase(Base* child, string fileName);// simply call addChild(child)
		Base* getChild();
		string getFileName();
		virtual bool executeCmd() = 0;
		void setFile(string fileName);
		void addChild(Base* child);
};
class OutputOverwrite: public DecoratorBase{/* > symbol*/
	public:
		OutputOverwrite(Base* child, string fileName):DecoratorBase(child, fileName){}
		virtual bool executeCmd();	//function should redirect output to a file,
									//call the child's executeCmd, then reset to the original stdOut slot
};
class OutputAppend: public DecoratorBase{/* >> symbol*/
	public:
		OutputAppend(Base* child, string fileName):DecoratorBase(child, fileName){}
		virtual bool executeCmd();
};
class InputRedirect: public DecoratorBase{/* < symbol*/
	public:
		InputRedirect(Base* child, string fileName):DecoratorBase(child, fileName){}
		virtual bool executeCmd();
};


#endif
