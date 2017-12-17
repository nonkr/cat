/*
 * Copyright (c) 2017, Billie Soong <nonkr@hotmail.com>
 * All rights reserved.
 *
 * This file is under GPL, see LICENSE for details.
 *
 * Author: Billie Soong <nonkr@hotmail.com>
 * Datetime: 2017/12/15 10:13
 *
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid;
    int   cnt = 0;
    pid = fork();
    if (pid < 0)
    {
        printf("error in fork!\n");
    }
    else if (pid == 0)
    {
        cnt++;
        printf("cnt=%d\n", cnt);
        printf("I am the child process,ID is %d\n", getpid());
    }
    else
    {
        cnt++;
        printf("cnt=%d\n", cnt);
        printf("I am the parent process,ID is %d\n", getpid());
    }
    return 0;
}