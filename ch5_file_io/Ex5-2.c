/**************************************************/
/* Ex5-2 - A program to add to an exisiting file. */
/* 						  */
/* Author: David Ogor				  */
/* Date: 06-03-2015				  */
/* 						  */
/* Purpose: Practice file I/O			  */
/**************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void process_file(const int fd)
{
  int res;
  char buf[] = "This is a test";

  res = lseek(fd, 0, SEEK_SET);
  if (res == -1) {
    perror("lseek");
    exit(1);
  }
  res = write(fd, buf, sizeof(buf));
  if (res < sizeof(buf)) {
    perror("write");
    exit(1);
  }
}
 
int main(int argc, char *argv[])
{
  int fd;
  
  if (argc == 1) {
    exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_WRONLY | O_APPEND);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  process_file(fd);
  close(fd);

  return 0;
}
