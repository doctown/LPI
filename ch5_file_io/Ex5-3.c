/********************************************************************************/
/* Ex5-3 Creates a file if necessary and appends a specified number of bytes to */
/*  the end of the file.						        */
/* 									        */
/* Author: David Ogor							        */
/* Date: 06-05-2015							        */
/* 									        */
/* Purpose: Demonstrate the importance of atomiticity.			        */
/********************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Write the character '0' to the file specified to number of bytes specified.
 *
 * params: fd - file descriptor
 *         num_bytes - number of bytes to be written
 */
void write_data(const int fd, const int num_bytes, const bool append)
{
  char *buf = malloc(sizeof(char) * BUFSIZ);
  int count = 0; 		/* number of bytes written */
  int res = 0; 			/* return value */
  buf = memset(buf, '0', BUFSIZ);
 
  while (count != num_bytes) {
    if (append) {
      lseek(fd, 0, SEEK_END);
    }
    if (num_bytes - count > BUFSIZ) {
      res = write(fd, buf, BUFSIZ);
      if (res != BUFSIZ) {
	perror("write");
	exit(1);
      }
      count += BUFSIZ;
    } else {
      int t_cnt = num_bytes - count; /* number of bytes left to be written */
      res = write(fd, buf, t_cnt);
      if ( res != t_cnt) {
	perror("write");
	exit(1);
      }
      count += t_cnt;
    } 
  }
  free(buf);
}

int main(int argc, char *argv[])
{
  int res = 0;
  int fd = 0;
  int num_bytes = 0;		/* number of bytes to write */
  int flags = 0;
  bool append_flag = false;	/* flag if x is passed */

  /* Verify that correct number arguments passed */
  if (argc != 3 && argc != 4) {
    error("Usage error: program_name filename num_of_bytes");
    exit(1);
  } else {
    res = sscanf(argv[2], "%d", &num_bytes);
    if (res != 1) {
      error("Number of bytes must be an integer.\n");
      exit(1);
    }
  }

  /* Read arguments and start function for writing to file. */
  flags = O_CREAT | O_WRONLY;
  if (argc == 4 && strcmp("x", argv[3])) {
    flags |= O_APPEND;
    printf("%s\n", argv[3]);
    append_flag = true;
  }
  fd = open(argv[1], flags);
  if (fd == -1) {
    perror("open");
  }
  write_data(fd, num_bytes, append_flag);
  
  close(fd);
  return 0;
}
