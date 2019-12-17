#ifndef PROCESS_CPP
#define PROCESS_CPP

#include <iostream>
#include "../header/process.h"

void Process::nextConnect() {
    if(current == 0 || current->getleft() == 0 || current->getright() == 0) {
        return;
    } //Checks if this is a connector with valid children
    
    if(current->getright()->getstate() != 0 ) {
	current = current->getparent();
        nextConnect();
        return;
    } //If both children are set, just process again at parrent

    int result = current->getleft()->getstate();
    std::string input = current->stored();

//std::cout << "nextConnect on: " << input << std::endl;

    if (result == 0) {
        current = current->getleft();
        nextConnect();
	return;
    } //Move to left child if not set

    if(input == "&&") {
        if(result == 1) {
            current->setstate(false);
            current = current->getparent();
	    nextConnect();
        }   
        else {
            current = current->getright();
            nextConnect();
        }
    } //Sets for && function
    else if(input == "||") {
        if(result == 1) {
            current = current->getright();
            nextConnect();
        }
        else {
            current->setstate(true);
            current = current->getparent();
	    nextConnect();
        }
    } // Sets for || function
    else if(input == ";") {
        current = current->getright();
        nextConnect();
    } // Sets for ; function
    else {
        std::cout << "Error: Unknown process to be next in Process:nextConnect" << std::endl;
    }
}

void Process::addTree(CCC* root) {
    first = true;
    current = root;
    while(current != 0 && current->getleft() != 0) {
    	current = current->getleft();
    }
    return;
}

std::string Process::next(bool result) {
    if(current == 0) {
	return "";
    }
    if(first) {
        first = false;
        return current->stored();
    } //Discards first input when getting first line
    current->setstate(result);
    current = current->getparent();
    nextConnect();
    if(current == 0) {
        return "";
    } //This to indicate input is done

    return current->stored();
}

#endif

