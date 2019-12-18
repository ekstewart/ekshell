#ifndef CCC_H
#define CCC_H

#include <string>
#include <vector>

using namespace std;

class CCC {
	protected:
		bool runStatus;
    public:
        CCC(){} //Constructor
        virtual bool executeCmd() = 0;
        
}; //Base for composite pattern

class Command: public CCC{
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

class Connect : public CCC {
	protected:
		CCC* left; //Left child
		CCC* right; //Right child
    public:
        Connect(CCC* left, CCC* right); //TODO: Implement to call addleft and addright functions
		CCC* getLeft() {return left; }
		CCC* getRight() {return right; }
		void addLeft(CCC* left);
		void addRight(CCC* right);

		virtual bool executeCmd() = 0;
}; //Connect class is for holding children and other connectors

class And : public Connect{
	public:
		And(CCC* left, CCC* right):Connect(left,right){}
		virtual bool executeCmd();
};
class Or : public Connect{
	public:
		Or(CCC* left, CCC* right):Connect(left,right){}
		virtual bool executeCmd();
};
class Semi : public Connect{
	public:
		Semi(CCC* left, CCC* right):Connect(left,right){}
		virtual bool executeCmd();
};

class PipeCon : public Connect{
	public:
		PipeCon(CCC* left, CCC* right):Connect(left,right){}
		virtual bool executeCmd();//Should open pipe, call executeCmd() on children, then close pipe ends
};

class DecoratorBase : public CCC{
	protected:
		CCC* decoChild;
		string fileName;
	public:
		DecoratorBase(CCC* child, string fileName);// simply call addChild(child)
		CCC* getChild();
		string getFileName();
		virtual bool executeCmd() = 0;
		void setFile(string fileName);
		void addChild(CCC* child);
};
class OutputOverwrite: public DecoratorBase{/* > symbol*/
	public:
		OutputOverwrite(CCC* child, string fileName):DecoratorBase(child, fileName){}
		virtual bool executeCmd();	//function should redirect output to a file,
									//call the child's executeCmd, then reset to the original stdOut slot
};
class OutputAppend: public DecoratorBase{/* >> symbol*/
	public:
		OutputAppend(CCC* child, string fileName):DecoratorBase(child, fileName){}
		virtual bool executeCmd();
};
class InputRedirect: public DecoratorBase{/* < symbol*/
	public:
		InputRedirect(CCC* child, string fileName):DecoratorBase(child, fileName){}
		virtual bool executeCmd();
};


#endif
