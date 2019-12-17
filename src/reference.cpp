#ifndef REFERENCE_CPP
#define REFERENCE_CPP

#include <iostream>

#include "../header/reference.h"

int Reference::match(const char character) {
    for(int i=0; i<ref.size(); i++) {
        if (character == ref.at(i).at(0)) {
            return i+1;
        }
    } //Loop that checks if the character matches the first char of a reference
    return 0;
}

int Reference::multimatch(const std::string input, const int pos, const int type) {
    std::string cur; //To save the current reference
    cur = ref.at(type - 1);
    for(int i=0; i<cur.size(); i++) {
        if(i + pos >= input.size() || input.at(pos + i) != cur.at(i)) {
	        return 0;
        }
    } //Loop to keep checking if all the character in a reference is in a string
    return type; 
}

Reference::Reference() {
    ref.push_back("&&"); //1 for and
    ref.push_back("||"); //2 for or
    ref.push_back(";"); //3 for connector
    ref.push_back("#"); //4 for comment
    ref.push_back("\""); //5 for ""
    ref.push_back("exit"); //6 for exit
    ref.push_back("("); //7 for (
    ref.push_back(")"); //8 for )
    ref.push_back("test"); //9 for test
    ref.push_back("["); // 10 for [
    ref.push_back("]"); // 11 for ]
    ref.push_back("<"); // 12 for <
    ref.push_back(">>"); // 13 for >>
    //ref.push_back(">"); // 14 for >
    //ref.push_back("|"); // 15 for |
 }

int Reference::check(const std::string input, int & i) {
    int cur = 0;
    for (i=0; i<input.size(); i++) {
        cur = match(input.at(i)); 
        
        if(cur == 0) {} //Pass on if not a connector
        /*
        else if (cur == 2 || cur == 13) {
            if(multimatch(input, i, cur) == cur) {
                ++i;
                return cur;
            }
            else {
                if(cur == 2) {
                    
                }
            }
        } //For connectors with both size 1 and 2 versions
        */
        else if (cur == 1 || cur == 2 || cur == 13) {
            if(multimatch(input, i, cur) == cur) {
                ++i;
                return cur;
            }
            
            else if(cur == 2) {
                return 15;
            } //For |
            
            else if(cur == 13) {
                return 14;
            } //For >
            
        } //For size two connectors
        
        else if (cur == 6 || cur == 9) {
            if(multimatch(input, i, cur) == cur) {
                i += 3;
                return cur;
            }
        } //For words of size 4
        
        else if (cur < 0 || cur > 13) {
            std::cout << "Error: Unknown case being checked in Reference::check" << std::endl;
        } //For invalid numbers
        
        else {
            return cur;
        } //For single size connectors
    }
    return 0;
}

#endif



