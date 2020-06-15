//
// Created by mengjie on 6/9/20.
//

#include "utils.h"

#include <errno.h>		/* for definition of errno */
#include <stdarg.h>		/* ISO C variable aruments */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
    char	buf[MAXLINE];

    vsnprintf(buf, MAXLINE-1, fmt, ap);
    if (errnoflag)
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s",
                 strerror(error));
    strcat(buf, "\n");
    fflush(stdout);		/* in case stdout and stderr are the same */
    fputs(buf, stderr);
    fflush(NULL);		/* flushes all stdio output streams */
}

/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 */
void
err_sys(const char *fmt, ...)
{
    va_list		ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

/*
 * Nonfatal error related to a system call.
 * Print a message and return.
 */
void
err_ret(const char *fmt, ...)
{
    va_list		ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}

char *get_env_command_prompt() {
    setenv("COMMAND_PROMPT", "->", 0);
    char* ret = getenv("COMMAND_PROMPT");
    return ret;
}

int pre_handle_command(char *command) {
    char* background = "bg", * ssetenv="export";
    // remove command front space
    int i = 0, j = 0;
    for(;command[i]==' '||command[i]=='\t';i++);
    for(;command[i]!='\0';j++)
        command[j] = command[i++];
    command[j] = '\0';

    if(strncmp(command, ssetenv, strlen(ssetenv))==0){
        for(j=strlen(ssetenv);command[j]==' ';j++);
        for (i=0;command[j]!='\0';i++,j++)
            command[i] = command[j];
        command[i] = '\0';
        return setenv_;
    }else if(strncmp(command,background,strlen(background))==0){
        for(i=0,j=strlen(background);command[j]!='\0';i++,j++)
            command[i]=command[j];
        command[i] = '\0';
        return nohup;
    } else
        return normal;
}
