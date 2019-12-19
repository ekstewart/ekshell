#ifndef PIPE_TEST_CPP
#define PIPE_TEST_CPP

#include "gtest/gtest.h"
#include "../src/base.cpp"
/**
 * Need to check to make sure that this operation:
 * 1.Opens a pipe
 * 2.Writes out output from pipe write to pipe read
 * 3.Closes pipe and continues writing out to original out (stdOut in this case)
 * 4.Works with parentheses (such as (echo h ; cat names.txt)| cat)
 */


TEST(PipeTest, SinglePipe){
	Base* a = new Command("echo \"This test\nis now\nbeing cat'd\"");
	Base* b = new Command("cat");
	Base* pipe = new PipeCon(a,b);
	
	pipe->executeCmd();
	
	Base* testCreated2 = new Command("echo \"This should be in stdOut!\"");
	testCreated2->executeCmd();
}
TEST(PipeTest, PipeWithIR){// cat < file | cat
	Base* cat = new Command("cat");
	Base* IR = new InputRedirect(cat, "PipeWithIR.txt");
	Base* cat2 = new Command("cat");
	Base* pipe = new PipeCon(IR,cat2);
	
	EXPECT_TRUE(pipe->executeCmd());
}

TEST(PipeTest, TwoPipes){//      (cat<existingInputFile | tr A-Z a-z > lowerCaseFile.txt && echo hello) | less
	Base* cat = new Command("cat");
	Base* catIR = new InputRedirect(cat,"existingInputFile");
	Base* trToLowerCase = new Command("tr A-Z a-z");
	Base* OOtr = new OutputOverwrite(trToLowerCase, "lowerCaseFile.txt");
	Base* pipe1 = new PipeCon(catIR,OOtr);
	
	Base* echo = new Command("cat names.txt");
	Base* andCon = new And(pipe1,echo);
	
	Base* andDecoOO = new OutputAppend(andCon, "bunchOfHellos.txt");
	
	Base* less = new Command("cat");
	Base* pipe2 = new PipeCon(andCon,less);
	
	EXPECT_TRUE(pipe2->executeCmd());
}



TEST(PipeTest, ParenPipe){// cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2
	
	Base* cat = new Command("cat");
	Base* catIR = new InputRedirect(cat,"existingInputFile");
	Base* trToLowerCase = new Command("tr A-Z a-z");
	Base* pipe1 = new PipeCon(catIR,trToLowerCase);
	std::cout<<"First pipe created"<<std::endl;
	
	Base* teeNewOut1 = new Command("tee newOutputFile1");
	Base* pipe2 = new PipeCon(pipe1,teeNewOut1);
	std::cout<<"Second pipe created"<<std::endl;
	
	
	Base* trToUpperCase = new Command("tr a-z A-Z");
	Base* trOO = new OutputOverwrite(trToUpperCase,"newOutputFile2");
	
	Base* pipe3 = new PipeCon(pipe2, trOO);
	std::cout<<"Third pipe created"<<std::endl;

	pipe3->executeCmd();
}


#endif
