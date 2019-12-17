#ifndef PIPE_TEST_CPP
#define PIPE_TEST_CPP

#include "gtest/gtest.h"
#include "../header/CCC.h"
#include "../src/command.cpp"
#include "../src/CCC.cpp"
/**
 * Need to check to make sure that this operation:
 * 1.Opens a pipe
 * 2.Writes out output from pipe write to pipe read
 * 3.Closes pipe and continues writing out to original out (stdOut in this case)
 * 4.Works with parentheses (such as (echo h ; cat names.txt)| cat)
 */


TEST(PipeTest, SinglePipe){
	CCC* a = new Command("echo \"This test\nis now\nbeing cat'd\"");
	CCC* b = new Command("cat");
	CCC* pipe = new PipeCon(a,b);
	
	pipe->executeCmd();
	
	CCC* testCreated2 = new Command("echo \"This should be in stdOut!\"");
	testCreated2->executeCmd();
}
TEST(PipeTest, PipeWithIR){// cat < file | cat
	CCC* cat = new Command("cat");
	CCC* IR = new InputRedirect(cat, "PipeWithIR.txt");
	CCC* cat2 = new Command("cat");
	CCC* pipe = new PipeCon(IR,cat2);
	
	EXPECT_TRUE(pipe->executeCmd());
}

TEST(PipeTest, TwoPipes){//      (cat<existingInputFile | tr A-Z a-z > lowerCaseFile.txt && echo hello) | less
	CCC* cat = new Command("cat");
	CCC* catIR = new InputRedirect(cat,"existingInputFile");
	CCC* trToLowerCase = new Command("tr A-Z a-z");
	CCC* OOtr = new OutputOverwrite(trToLowerCase, "lowerCaseFile.txt");
	CCC* pipe1 = new PipeCon(catIR,OOtr);
	
	CCC* echo = new Command("cat names.txt");
	CCC* andCon = new And(pipe1,echo);
	
	CCC* andDecoOO = new OutputAppend(andCon, "bunchOfHellos.txt");
	
	CCC* less = new Command("cat");
	CCC* pipe2 = new PipeCon(andCon,less);
	
	EXPECT_TRUE(pipe2->executeCmd());
}



TEST(PipeTest, ParenPipe){// cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2
	
	CCC* cat = new Command("cat");
	CCC* catIR = new InputRedirect(cat,"existingInputFile");
	CCC* trToLowerCase = new Command("tr A-Z a-z");
	CCC* pipe1 = new PipeCon(catIR,trToLowerCase);
	std::cout<<"First pipe created"<<std::endl;
	
	CCC* teeNewOut1 = new Command("tee newOutputFile1");
	CCC* pipe2 = new PipeCon(pipe1,teeNewOut1);
	std::cout<<"Second pipe created"<<std::endl;
	
	
	CCC* trToUpperCase = new Command("tr a-z A-Z");
	CCC* trOO = new OutputOverwrite(trToUpperCase,"newOutputFile2");
	
	CCC* pipe3 = new PipeCon(pipe2, trOO);
	std::cout<<"Third pipe created"<<std::endl;

	pipe3->executeCmd();
}


#endif