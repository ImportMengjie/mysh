//
// Created by mengjie on 6/9/20.
//

#ifndef MYSH_UTILS_H
#define MYSH_UTILS_H

#include <stdio.h>

#define	MAXLINE	4096			/* max line length */

enum COMMAND_TYPE{
    normal=1,nohup,setenv_
};

static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap);

void	err_sys(const char *, ...) __attribute__((noreturn));

void	err_ret(const char *, ...);

char* get_env_command_prompt();

int pre_handle_command(char* command);

#endif //MYSH_UTILS_H
