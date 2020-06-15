#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"

bool need_prompt = true;

void sig_int(int signo)
{
    printf("\n%s ", get_env_command_prompt());
    need_prompt = false;
}

int main(){
    char buf[MAXLINE];
    pid_t pid;
    int status;

    if(signal(SIGINT, sig_int)==SIG_ERR)
        err_sys("signal error");
    printf("%s ", get_env_command_prompt());
    while (fgets(buf,MAXLINE,stdin)!=NULL){
        int command_type = pre_handle_command(buf);

        if(buf[strlen(buf)-1]=='\n')
            buf[strlen(buf)-1]='\0';
        if(command_type==nohup||command_type==normal){
            if((pid=fork()) < 0)
                err_sys("fork error");
            else if(pid==0){
                system(buf);
//                execl("/bin/sh", "sh", "-c", buf, NULL);
                exit(127);
            }
            else if(command_type==normal&&(pid=waitpid(pid, &status, 0))<0)
                err_sys("wait pid error");
        }
        else if(command_type==setenv_)
            if(putenv(buf)<0)
                err_sys("error put env: %s", buf);


        if(need_prompt)
            printf("%s ", get_env_command_prompt());
        else
            need_prompt = !need_prompt;
    }
    return 0;
}
