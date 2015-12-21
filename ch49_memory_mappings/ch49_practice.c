#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

void mmap_practice(const int, const int);

int main(int argc, char *argv[])
{
  int fd = 0;
  char buf[100];
  int flag = O_RDONLY;
  char c = '\0';
  int bytes_read = 0;
  int count_bytes = 0;
  struct stat sb;

  printf("Enter the file to be modified:");
  fgets(buf, sizeof(buf), stdin);
  buf[strlen(buf) - 1] = '\0';

  fd = open(buf, flag);
  if (fd == -1) {
    fprintf(stderr, "Cannot open file %s", buf);
    exit(1);
  }
  /*
  while ((bytes_read = read(fd, &c, 1)) > 0) {
    putchar(c);
    count_bytes++;
  }
  */
  if (fstat(fd, &sb) == -1) {
    fprintf(stderr, "fstat failed");
    exit(1);
  }
  
  mmap_practice(fd, sb.st_size);
  close(fd);
  return 0;
}

/* 
 * Practice using mmap by mapping to a file and seeing if it can be update from the virtual memory location.
 */
void mmap_practice(const int fd, const int count)
{
  char *map_addr = NULL;

  map_addr = mmap(NULL, count, PROT_NONE, MAP_SHARED, fd, 0);
  if (MAP_FAILED == map_addr) {
    fprintf(stderr, "mmap failed");
    exit(1);
  }
  *map_addr = 'O';
  
}
