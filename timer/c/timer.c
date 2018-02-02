/*
 * Copyright (c) 2017, Billie Soong <nonkr@hotmail.com>
 * All rights reserved.
 *
 * This file is under GPL, see LICENSE for details.
 *
 * Author: Billie Soong <nonkr@hotmail.com>
 * Datetime: 2018/1/29 19:00
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

void printMsg(int num)
{
    printf("%s", "Hello World!!\n");
}

int main()
{
    // Register printMsg to SIGALRM
    signal(SIGALRM, printMsg);

    struct itimerval tick;

    // Initialize struct
    memset(&tick, 0, sizeof(tick));

    // Timeout to run function first time
    tick.it_value.tv_sec  = 1; // sec
    tick.it_value.tv_usec = 0; // micro sec.

    // Interval time to run function
    tick.it_interval.tv_sec  = 1; // sec, set zero for one shot
    tick.it_interval.tv_usec = 0; // micro sec.

    // Set timer, ITIMER_REAL : real-time to decrease timer, send SIGALRM when timeout
    if (setitimer(ITIMER_REAL, &tick, NULL))
    {
        printf("Set timer failed!!/n");
    }

    while (1)
    {
        pause();
    }

    return 0;
}