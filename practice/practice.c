#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* practice truncating a file */
void test_truncate() {
  int fd = open("test.txt", O_RDWR);
  if (fd == -1) {
    perror("open");
    exit(1);
  }
  
  if (ftruncate(fd, 1000) == -1) {
    perror("ftruncate");
    exit(1);
  }

  char buf[BUFSIZ];
  int res = 0;
  do {
    res = read(fd, buf, BUFSIZ);
    if (res == -1) {
      perror("read");
      exit(1);
    }
    if (write(STDOUT_FILENO, buf, res) == -1) {
      perror("write");
      exit(1);
    }
  } while (res != 0);
  close(fd);
}
/* opening and seeking through a file with lseek */
void test_lseek()
{
  int flags = O_RDONLY;
  char buf[BUFSIZ];

  int fd = open("test.txt", flags);
  if (fd == -1) {
    perror("open");
    exit(1);
  }
  int count;
  lseek(fd, 8, SEEK_END);
  while ((count = read(fd, buf,BUFSIZ)) > 0) {
    write(1, buf, count);  
  }
}
  
int main(int argc, char * argv[])
{
  test_truncate();
  return 0;
}
