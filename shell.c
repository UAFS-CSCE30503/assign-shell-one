#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 20

/***********************************************************************
 * This starter shell implements a simple shell that implements:
 * 
 * (1) An internal EXIT command that exits the shell.
 * (2) Executes a external program without any command line arguments
 * 
 ***********************************************************************/
int main(int argc, char *argv[]){
    char buffer[BSIZE];
    pid_t child;
    int status;
    char *args[]={"",NULL};

    while(1){
        printf("shell> ");
        fgets(buffer,BSIZE-1,stdin);
        buffer[(strlen(buffer)-1)]='\0';  //Remove NewLine
        args[0]=buffer;

        //** Internal Command **
        if(strcmp(buffer,"exit")==0){
            break;
        }
        //** External Command **
        child = fork();
        if(child==0){
            //*** Child Process ***
            execvp(args[0],args);
            exit(0);
        }else{
            //*** Parent Process **
            waitpid(-1,&status,0);
        }

    }
    return 0;
}