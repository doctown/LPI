#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define MAX_READ 50
#define ERR(msg) {perror(msg); exit(EXIT_FAILURE);}


int read_input(int fd);
int read_opt(int argc, char *argv);
int main(int args, char *argv[])
{
  int fd, flags;;
  mode_t mode;
  flags = O_RDWR | O_CREAT;
  mode = S_IRWXU | S_IRWXG | S_IRWXO;

  fd = open(argv[1], flags, mode);
  if (fd == -1)
    ERR("open");
  read_input(fd);
  if (close(fd) == -1)
    ERR("close");

  return 0;
}

int read_input(int fd)
{
  char buf[MAX_READ];
  ssize_t res;

  while ((res = read(STDIN_FILENO, buf, MAX_READ)) > 0) {
    write(fd, buf, res);
    write(STDOUT_FILENO, buf, res);
  }

  if (res < 0) {
    //print error messsage
    return -1;
  }

  
  return 1;
}
