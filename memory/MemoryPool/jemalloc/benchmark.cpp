/*
 * Copyright (c) 2018, Billie Soong <nonkr@hotmail.com>
 * All rights reserved.
 *
 * This file is under MIT, see LICENSE for details.
 *
 * Author: Billie Soong <nonkr@hotmail.com>
 * Datetime: 2018/9/1 16:05
 *
 */

#include <cstdlib>
#include <cstdio>
#include <pthread.h>

#define NUM_THREADS    5
#define MAX_MALLOC_NUM (1000 * 1000 * 10)

void *TestRoutine(void *arg)
{
    int  i = MAX_MALLOC_NUM;
    char *p1;
    while (i--)
    {
        p1 = new char[100];
        delete[] p1;
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int       rc;
    long      t;
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, TestRoutine, NULL);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
    }

    return 0;
}
