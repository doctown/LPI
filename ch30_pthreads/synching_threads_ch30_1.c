/****************************************************************************************************************************************************************/
/* Ex: 30-1 - Update a program that uses two threads to count up to number specified by the user. Use mutexes to ensure that the numbers are updated correctly. */
/* 																			        */
/* Original: LPI																	        */
/* Author: David Ogor																	        */
/* Date: 08-08-2015																	        */
/* 																			        */
/* usage:																		        */
/****************************************************************************************************************************************************************/



/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2015.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 30-1 */

/* thread_incr.c

   This program employs two POSIX threads that increment the same global
   variable, without using any synchronization method. As a consequence,
   updates are sometimes lost.

   See also thread_incr_mutex.c.
*/
#include <pthread.h>
#include "tlpi_hdr.h"

struct info {
  int id;
  int loops;
};

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static volatile int glob = 0;   /* "volatile" prevents compiler optimizations
                                   of arithmetic operations on 'glob' */
static void *                   /* Loop 'arg' times incrementing 'glob' */
threadFunc(void *arg)
{
    struct info *i = (struct info *) arg;
    int loops = i->loops; 
    int loc, j;

    //TODO: Implement a mutex
    for (j = 0; j < loops; j++) {
      pthread_mutex_lock(&mtx);
        loc = glob;
        loc++;
        glob = loc;
	pthread_mutex_unlock(&mtx);
    }

    printf("Thread %d - glob total: %d\n", i->id, glob);
    return NULL;
}

int
main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;

    loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000;

    struct info info1;
    info1.id = 1;
    info1.loops = loops;

    struct info info2;
    info2.id = 2;
    info2.loops = loops;

    s = pthread_create(&t1, NULL, threadFunc, (void *) &info1);
    if (s != 0)
        errExitEN(s, "pthread_create");
    s = pthread_create(&t2, NULL, threadFunc,  (void *) &info2);
    if (s != 0)
        errExitEN(s, "pthread_create");

    s = pthread_join(t1, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");
    s = pthread_join(t2, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    printf("glob = %d\n", glob);
    exit(EXIT_SUCCESS);
}
