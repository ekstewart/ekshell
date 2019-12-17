#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int main(){
    int pipefd[2];
    pid_t pid;
    char buffer;

    if(pipe(pipefd)== -1){
        perror("pipe error");
        exit(1);
    }


    pid = fork();
    int stdOutLocation = dup(1);
    int stdInLocation = dup(0);


    if(pid <0){
        perror("pipe error");
        exit(1);
    }
    if(pid == 0){//child reads from pipe
        close(pipefd[1]); //close write end
        dup2(pipefd[0],0)

        string input = "";
        while(read(0,&buffer,SSIZE_MAX))
        {
            input+= buffer;
        }

    }
    else if(pid > 0){//parent writes to pipe
        close(pipefd[0]); //close read end
        dup2(pipefd[1],1);//inserts write end into stdOut cell



    }
}