#ifndef READ_CPP
#define READ_CPP
 
#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <typeinfo>
#include "../header/read.h"

bool Read::invalidRoot() {
    if(croot == 0 && droot == 0 || croot == 0 && root == 0 || droot == 0 && root == 0) {
        return false;
    }
    return true;
}

void Read::setTop(Connect* temp) {
    croot = temp;
    droot = 0;
    root = 0;
}

void Read::setTop(DecoratorBase* temp) {
    droot = temp;
    croot = 0;
    root = 0;
}

void Read::setTop(Command* temp) {
    root = temp;
    croot = 0;
    droot = 0;
}

CCC* Read::getTop() {
    if(invalidRoot()) {
        std::cout << "Error: Root node improperly set Read::getTop" << std::endl;
    }
    if(croot != 0) {
        return croot;
    }
    else if(droot != 0) {
        return droot;
    }
    else if(root != 0) {
        return root;
    }
    return 0;
}

int Read::top() {
    if(invalidRoot()) {
        std::cout << "Error: Root node improperly set Read::top" << std::endl;
    }
    if(croot != 0) {
        return 1;
    }
    else if(droot != 0) {
        return 2;
    }
    else if(root != 0) {
        return 3;
    }
    return 0;
}

int Read::top(CCC* temp) {
    if(temp == 0) {
        return 0;
    }
    if(typeid(temp) == typeid(Connect)) {
        return 1;
    }
    if(typeid(temp) == typeid(DecoratorBase)) {
        return 2;
    }
    if(typeid(temp) == typeid(Command)) {
        return 3;
    }
    return 0;
}

Command* Read::makeLeaf(std::string & total) {
    if(total == "") {
        return 0;
        //total = " ";
        //std::cout << "Error: empty node trying to be made Read::makeLeaf" << std::endl;
    }
    total.erase(total.size()-1);
    Command* temp = new Command(total);
    v.push_back(temp);
    total = "";
    return temp;
}

void Read::addLeaf(std::string & total) {
    if(total == "") {
        return;
    }
    Command* temp = makeLeaf(total);
    int type = top();
    if(type == 0) {
        setTop(temp);
    }
    else if(type == 1) {
        if(croot->getRight() == 0) {
            croot->addRight(temp);
            return;
        }
        std::cout << "Error: calling Read::addLeaf on a full connector" << std::endl;
    }
    else {
        std::cout << "Error: decorator/leaf should not call Read::addLeaf" << std::endl;
    }
} //For end of input or right child

void Read::addConnector(Connect* c, std::string & total) {
    CCC* temp;
    int type = top();
    if(type == 0) {
        temp = makeLeaf(total);
        c->addLeft(temp);
    }
    else {
	addLeaf(total);
        c->addLeft(getTop());
    }
    setTop(c);
    v.push_back(c);
} //Assume Connect has no children when passed in

void Read::addDecor(DecoratorBase* d, std::string & split, std::stringstream & ss, const int cur2) {
    std::string temp;
    int t, type;
    Reference r;    

    v.push_back(d);
    
    if(split != "") {
        d->setFile(split);
        split = "";
    } //Sets file for decor
    else {
        ss >> temp;
	type = r.check(temp, t);
	if(type != 0) {
	    split = splitInput(temp, type, t, false);
	}

        d->setFile(temp);
    } //Sets file for decor
    
    t = top();
    if(t == 0) {}
    else if(t == 1 && cur2 != 8) {
        d->addChild(croot->getRight());
        croot->addRight(d);
        return;
    }
    else {
        d->addChild(getTop());
    }
    
    setTop(d);
}

void Read::addTree(CCC* c) {
    int type = top();
    if(type == 0) {
        std::cout << "Error: addTree does not work for empty root" << std::endl;
    }
    else if(type == 1) {
        croot->addRight(c);
    }
    else if(type == 2 || type == 3) {
        std::cout << "Error: No connector between parentheses" << std::endl;
        exit(-1);
    }
} //For parentheses and assume that top node is not empty

void Read::removeTree() {
    for(int i=0; i<v.size(); i++) {
        delete v.at(i);
    }
    v.clear();
    croot = 0;
    droot = 0;
    root = 0;
}

std::string Read::splitInput(std::string & input, const int type, const int pos, const bool quote) {
    std::string second;
    second = "";

    if(input == "") {
        return "";
    } //Check for empty string
    
    if(quote) {
    	if(type == 5) {
    	    if(input.size() == 1) {
    	        return "";
    	    }
    	    if(pos > 0) {
    	        second = input.substr(pos);
    	        input.erase(pos);
    	    }
    	    else {
    	        second = input.substr(pos + 1);
    	        input = input.at(0);
    	    }
    	}
    	return second;
    }
    
    if(type == 1 || type == 2 || type == 13) {
        if(input.size() == 2) {
            return "";
        }
        if(pos > 1) {
            second = input.substr(pos - 1);
            input.erase(pos - 1);
        }
        else {
            second = input.substr(pos + 1);
            input.erase(pos + 1);
        }
    } //For connectors of size 2
    else if (type == 6 || type == 9) {
        if(input.size() == 4) {
            return "";
        }
        if(pos > 3) {
            second = input.substr(pos - 3);
            input.erase(pos - 3);
        }
        else {
            second = input.substr(pos + 1);
            input.erase(pos + 1);
        }
    } //For connectors of size 4
    else if (type == 0) {} //For commands
    else if (type < 0 || type > 15) {
        std::cout << "Error: Unknown process for splitting in splitInput" << std::endl;
    } 
    else {
        if(input.size() == 1) {
            return "";
        }
    	if(pos == 0) {
    	    second = input.substr(pos+1);
    	    input = input.at(0);
    	}
        else {
            second = input.substr(pos);
            input.erase(pos);
        }
    } //For connectors of size 1
    return second;
} //Splits input depending if the command or connector is in front

void Read::testEnd(std::string & total, bool & test) {
    /*if(total == "") {
    	total = " ";
    }*/
    if(test) {
        total += "] ";
        test = false;
    }
}

void Read::checkBrackets(std::stack<Connect*> sub, bool test2) {
    if(sub.size() != 0 || test2 == true) {
	    std::cout << "Unclosed parentheses/brackets detected, exiting programing" << std::endl;
        exit(-1);
    }
}

bool Read::justSpace(std::string input) {
    for(int i=0;i<input.size(); ++i) {
    	if(!isspace(input.at(i))) {
    	    return false;
    	}
    }
    return true;
}

void Read::makeTree(std::string input) {
    int cur, pos, cur2; //Holds current type of input, and pos hold position of conector
    std::string hold, total, split; //Hold for current word, total is for saved input string, splut for when hold is split
    std::stringstream ss;
    bool quote, test, test2; //Used to indicate if inside a two part symbol like parentheses
    std::stack<Connect*> sub;
    CCC* temp = 0;
    Reference ref;
    ss << input;
    quote = false;
    test = false;
    test2 = false;
    cur2 = 0;
 
    while (ss >> hold) {
        do {
    	    cur = ref.check(hold, pos); //Gets the first recognized control or special command in the word
    	    split = splitInput(hold, cur, pos, quote); //Splits word if contains multiple commands or control
    	    cur = ref.check(hold, pos);
		
    	    if(quote) {
        		if(cur == 5) {
        		    quote = false;
        		    total.erase(total.size()-1);
        		    total += hold;
        		    total += " ";
        		    testEnd(total, test);
    	        }
    	    	else {
        		    total += hold;
        		    total += " ";
    	    	}
    	    } //Ignore all other commands until other quote is found
	    
	        else {
                switch(cur) {
                    case 0: //Commands
                        total += hold;
                        total += " ";
                        break;
                    case 1: //&&
			testEnd(total, test);
                        addConnector(new And(0,0), total);
                        break;
                    case 2: //||
			testEnd(total, test);
                        addConnector(new Or(0,0), total);
                        break;
                    case 3: //;
			    testEnd(total, test);
    		            addConnector(new Semi(0,0), total);
                        break;
                    case 4: //#
                        if(total != "") {
                            testEnd(total, test);
                            addLeaf(total);
                        }
			            checkBrackets(sub, test2);
                        return;
                        break;
                    case 5: //""
                        quote = true;
                        total += "\"";
			            total += split;
			            total += " ";
			            split = "";
                        break;
                    case 6: //exit
                        if(pos == 3 && total == "") {
                            //testEnd(total, test);
                            hold = "exit ";
                            addLeaf(hold);
			                checkBrackets(sub, test2);
                            return;
                        }
                        total += hold;
                        total += " ";
                        break;
                    case 7: //(
                        addLeaf(total);
                        /*if(top() == 2) {
                            std::cout << "Error building tree with parenthesis in Read::makeTree" << std::endl;
                        }*/
			if(top() == 1) {
                            sub.push(croot);
                            croot = 0;
                            droot = 0;
                            root = 0;
			}
			else {
			    sub.push(0);
			}
                        break;
                    case 8: //)			
            			/*if(total == "") {
            			    total = " ";
            			}*/
            			testEnd(total, test);
            			addLeaf(total);
            
            			if(sub.empty()) {
            			    checkBrackets(sub, true);
            			}//Calls error for extra closing brackets
                        
            			temp = getTop();
                        if(sub.top() == 0) {
                            sub.pop();
                            break;
                        }
			setTop(sub.top());
                        addTree(temp);
            			sub.pop();
            			break;
                    case 9: //test
                        if(!test) {
                            test = true;
                            total += "[ ";
                        }
                        break;
        		    case 10: //[
        		        addLeaf(total);
            			test2 = true;
            			total += "[";
            			total += " ";
            			break;
        		    case 11: //]
            			if(!test2) {
            			    checkBrackets(sub, true);
            			} //Calls error for extra closing brackets
            			test2 = false;
            			total += "]";
            			total += " ";
            			break;
            		case 12: // <
			    testEnd(total, test);
            		    addLeaf(total);
            		    addDecor(new InputRedirect(getTop(), ""), split, ss, cur2);
            		    break;
            		case 13: // >>
			    testEnd(total, test);
            		    addLeaf(total);
            		    addDecor(new OutputAppend(getTop(), ""), split, ss, cur2);
            		    break;
            		case 14: // >
			    testEnd(total, test);
            		    addLeaf(total);
            		    addDecor(new OutputOverwrite(getTop(), ""), split, ss, cur2);
            		    break;
            		case 15: // |
            		    addConnector(new PipeCon(0,0), total);
            		    break;
                    default:
                        std::cout<<"Error: Unknown result for Read::makeTree" << std::endl;
                        break;
                }
            }
	        hold = split;
	        cur2 = cur;
	    } while(split != ""); //Runs once then checks to see if input was split
    } //Process through the entire user input
    if (total != "") {
        testEnd(total, test);
        addLeaf(total);
    }
    checkBrackets(sub, test2);
}

CCC* Read::inputTree() {
    std::string input;
    do {
	    std::cout << "$ ";
	    std::getline(std::cin, input);
    } while(justSpace(input));

    removeTree();
    makeTree(input);
    return getTop();
}

CCC* Read::TESTINGinputTree(std::string input) {
    removeTree();
    makeTree(input);
    return getTop();
} //Only for unit tests

#endif
