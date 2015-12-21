/*******************************************************************************/
/* Listing 5-3: Accessing large files					       */
/* ––––––––––––––––––––––––––––––––––––––––––––––––––––––– fileio/large_file.c */
/*******************************************************************************/
#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
//#include "tlpi_hdr.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define usageErr(msg, arg) {perror(msg);printf("%s",arg);}
#define errExit(msg) {perror(msg); exit(1);}


int main(int argc, char *argv[]) {
  int fd;
  off64_t off;

  if (argc != 3 || strcmp(argv[1], "--help") == 0)
    usageErr("%s pathname offset\n", argv[0]);
  fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  if (fd == -1)
    errExit("open64");
  off = atoll(argv[2]);
  if (lseek64(fd, off, SEEK_SET) == -1)
    errExit("lseek64");
  if (write(fd, "test", 4) == -1)
    errExit("write");
  exit(EXIT_SUCCESS);
}
