#ifndef DECO_TEST_CPP
#define DECO_TEST_CPP

#include "gtest/gtest.h"
#include "../header/CCC.h"
#include "../src/command.cpp"
using namespace std;
/**
 * Need to check to make sure that the overwrite/append operations:
 * 1.Open up the output stream properly
 * 2.Create file if necessary
 * 3.Ensure that these objects return false appropriately
 * 4.Ensure that these objects work with multiple layers of parentheses
 * 5.Restore output stream to stdOut
 */
 
//TESTING THE '>' OPERATOR
TEST(OverwriteTest, OverwriteFromSingleCommand){
	CCC* a = new Command("echo INYOURFILE");
	CCC* b = new Command("echo \"Overwrite in stdOut\"");
	cout<<"created two echo commands, a and b"<<endl;
	cout<<"Calling OW to OverwriteTest.txt"<<endl;
	CCC* OW = new OutputOverwrite(a, "OverwriteTest.txt");
	
	cout<<"Running OW"<<endl;
	OW->executeCmd();
	
	cout<<"Running additional echo for stdOut..."<<endl;
	b->executeCmd();
}


//TESTING THE '>>' OPERATOR
TEST(AppendTest, AppendFromSingleCommand){
	CCC* a = new Command("echo \"OH NOW IM REALLY IN YOUR FILE\"");
	CCC* b = new Command("echo \"Overwrite in stdOut\"");
	cout<<"created two echo commands, a and b"<<endl;
	cout<<"Calling AP to AppendThis.txt"<<endl;
	CCC* OW = new OutputAppend(a, "AppendThis.txt");
	
	cout<<"Running AP"<<endl;
	OW->executeCmd();
	
	cout<<"Running additional echo for stdOut..."<<endl;
	b->executeCmd();
}

//TESTING THE '<' OPERATOR
TEST(InputRedirectTest, RedirectToCat){
	CCC* a = new Command("cat");
	CCC* IR = new InputRedirect(a,"OverwriteTest.txt");
	
	IR->executeCmd();
}
TEST(InputRedirectTest, RedirectInputWithParentheses){// (echo hello && cat) < IRText.txt
	CCC* a = new Command("echo hello");
	CCC* b = new Command("cat");
	CCC* andCon = new And(a,b);
	CCC* IR = new InputRedirect(andCon,"IRText.txt");
	
	IR->executeCmd();
}

#endif