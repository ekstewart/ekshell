#ifndef REFERENCE_H
#define REFERENCE_H

#include <string>
#include <vector>

class Reference {
    private:
        std::vector<std::string> ref; //Stores the valid connectors
        
        int match(char character); //Checks if a character has a matching symbol
        int multimatch(const std::string input, const int pos, const int type); //Vertifies if an entire command is called given a string, type, and position
    public:
        Reference();
        int check(const std::string input, int & i); //Check if a string has a matching input and returns position of current location
};

// 0 for no connectors or specal word
// 1 for &&
// 2 for ||
// 3 for ;
// 4 for #
// 5 for "
// 6 for exit
// 7 for (
// 8 for )
// 9 for test
// 10 for [
// 11 for ]
// If more are added update reference, CCC, and Read
#endif
