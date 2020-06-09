#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "utils.h"

void sig_int(int signo)
{
    printf("interrupt\n%% ");
}

int main(){
    char buf[1024];
    pid_t pid;
    int status;

    if(signal(SIGINT, sig_int)==SIG_ERR)
        err_sys("signal error");
    printf("%% ");
    while (fgets(buf,MAXLINE,stdin)!=NULL){
        if(buf[strlen(buf)-1]=='\n')
            buf[strlen(buf)-1]='\0';
        if((pid=fork()) < 0)
            err_sys("fork error");
        else if(pid==0){
            system(buf);
        }
        else if((pid=waitpid(pid, &status, 0))<0)
            err_sys("waitpid error");
        printf("%% ");
    }
    return 0;
}
