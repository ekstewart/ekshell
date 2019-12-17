#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

int main(){
	//Call fork and store the child and parent pid's in thisPid
	pid_t thisPid = fork();

	//PError case if pid is -1
	if(thisPid == -1)
	{		
		std::cout<<"Error occurred in pid = "<<thisPid<<std::endl;
	}
	//Child case if pid is 0
	else if(thisPid == 0)
	{
		std::cout<<"Child pid, thisPid is = "<<thisPid<<std::endl;
	}
	//Parent case if pid is above 0 (some arbitrary id number)
	else//(thisPid > 0) else must occur if previous cases do not occur
	{
		std::cout<<"Parent pid, thisPid is = "<<thisPid<<std::endl;
		//call waitpid with 0(which is the child's pid) to wait for the child to finish
		waitpid(0);
	}
	return 0;
}
