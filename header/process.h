#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "base.h"

class Process {
    private:
        CCC* current; // current hold the current node being read
        bool first;
        
        void nextConnect(); //Checks a connect node and move current to the correct node
    public:
        Process(): current(0) {}
        void addTree(CCC* root); // Sets the current node in the tree
        std::string next(bool result); //Given the result of the previous command, this will output the next command to be run, returns "" at end
};

#endif
