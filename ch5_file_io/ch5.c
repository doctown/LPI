#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void dup_test(void) {
  int fd, flags;
  flags = O_RDONLY;
  fd = open("ch5.c", flags);
  if (fd == 0) {
    perror("open");
    exit(1);
  }

  int newfd = dup(fd);
  int results; 
  char buf[BUFSIZ];
  
  printf("Old file descriptor = %d\nNew file descriptor = %d\n", fd, newfd);
  //while ((read(newfd, buf, BUFSIZ)) != 0)
    //    puts( buf);

  close(fd);
  close(newfd);inux programming in
}

int main(int argc, char *argv[]) {
  dup_test();

  return 0;
}
