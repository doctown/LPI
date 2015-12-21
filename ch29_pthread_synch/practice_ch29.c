/***************************************************/
/* practice - a practice file for creating threads */
/***************************************************/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *func(void * var)
{
  printf("Entering function!\n");
  int cnt = 0;

  while (cnt++ < 20) {
    printf("Working ...");
    sleep(1);
  }

  pthread_exit(0);
}


int main(int argc, char *argv[])
{
  pthread_t t1;
  int ret = 0;


  ret = pthread_create(&t1, NULL, func, NULL);

  if (ret != 0) {
    perror("pthread_create");
    exit(1);
  }

  printf("Main thread continuing\n");
  
  pthread_join(t1, NULL);
  //sleep(10);
  printf("Program ends\n");

  return 0;
}
