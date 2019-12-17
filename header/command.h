#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include <vector>
using namespace std;

class Command{
    private:
        vector<string> parsedCmdList;
        vector<char*> args;
        bool exitCalled;

        string trimWhitespace(string input); // Helper function to clean up leading and trailing whitespace in a string
        void parseToStringVector(string cmdString); // Helper function to convert a string to a vector<string>
                    // With the first index[] being the executable and the following being arguments
        void convertToCStringVector(); // Helper function to convert the vector<string> to vector<char*>
        void callTestCommand(); // Helper function that executes 'test' or [<command>] functionality

        bool runStatus;
    public:
        Command(string argList); // Constructor, expects entire command string as parameter
        bool executeCmd(); // Function that calls execvp and returns exit status. TRUE if exited, FALSE if didnt exit correctly
        inline vector<string> getParsedCmdList(){return parsedCmdList;} // ONLY FOR TESTING PURPOSES
};



#endif
