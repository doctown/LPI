/***************************************************/
/* simple-thread -  A thread tries to join itself. */
/* 		    Outcome:			   */
/* Author: David Ogor				   */
/* Date: 07-31-2015				   */
/***************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/*
 * Adds 1 to  number and return value.
 *
 * Returns number plus 1.
 */
void *plusOne(void *arg) 
{
  int *num = (int *) arg;
  int res = 0;

  *num = *num + 1;
  
  res = pthread_join(pthread_self(), NULL);
  printf("Thread join results = %d\n", res); 
  pthread_exit(num);
}

int main(int args, char *argv[])
{
  pthread_t thread;
  int res = 0; 			/* return value */
  int n = 2;
  void *retval;			/* thread return value */

  res = pthread_create(&thread, NULL, plusOne, &n);
  if (res != 0) {
    perror("pthread_create");
    exit(1);
  }

  pthread_join(thread, &retval);
  
  printf("Number = %d\nProgram Exiting\n", *((int *) retval));
  return 0;
}
