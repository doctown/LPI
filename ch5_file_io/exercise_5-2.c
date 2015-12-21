/********************************************************************************************/
/* 5-2. Write a program that opens an existing file for writing with the O_APPEND flag, and */
/* then seeks to the beginning of the file before writing some data. Where does the	    */
/* data appear in the file? Why?							    */
/********************************************************************************************/
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
  int fd, flags;
  flags = O_RDWR | O_APPEND;
  //open an existing file with O_APPEND flag
  fd = open("temp.txt", flags);
  if (fd == 0) {
    perror("open");
    exit(1);
  }

  //seek to the beginning of the file
  lseek(

//write some data

  return 0;
}
