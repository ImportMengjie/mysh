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
