//
// Created by mengjie on 6/9/20.
//

#ifndef MYSH_UTILS_H
#define MYSH_UTILS_H

#include <stdio.h>

#define	MAXLINE	4096			/* max line length */

static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap);

void	err_sys(const char *, ...) __attribute__((noreturn));

void	err_ret(const char *, ...);

#endif //MYSH_UTILS_H
