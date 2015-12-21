/**********************************************/
/* Implementation of dup and dup2 using fcntl */
/* 					      */
/* Author: David Ogor			      */
/* Date: 06-13-2015			      */
/* 					      */
/* Purpose: Practice file I/O implementation  */
/**********************************************/


#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int dup_t(const int oldfd)
{
  int flags;
  int newfd;
  
  flags = fcntl(oldfd, F_GETFL);
  if (flags == -1) {
    perror("fcntl");
    exit(1);
  }

  newfd = fcntl(oldfd, F_DUPFD, oldfd);
  if (newfd == -1) {
    perror("fcntl");
    exit(1);
  }

  return newfd;
}


int main(int argc, char *argv[]) 
{
  int fd;

  fd = dup_t(STDOUT_FILENO);
  
  
  write(fd, "Test\n", 5);
 
  return 0;
}
