/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2015.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/***************************************************/
/* Ex5-1 - Updating the file.			   */
/* Author: David Ogor				   */
/* Date: 05-29-2015				   */
/* 						   */
/* Purpose: Practice concepts in chapter 5 for I/O */
/* Instructions:*/
/***************************************************/

/* Listing 5-3 */

/* large_file.c

   Demonstrate the use of the (obsolete) Large File System API.

   This program is Linux-specific.
*/
#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int fd;
    off64_t off_64;
    off_t off;
    int flags = O_CREAT | O_RDWR;
    mode_t mode = S_IRUSR | S_IWUSR;
    int status = 0;
    int numWritten = 0;

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname offset\n", argv[0]);

    fd = open(argv[1], flags, mode);
    if (fd == -1)
      errExit("open");

    off = atoll(argv[2]);
    status = lseek(fd, off, SEEK_SET);
    if (status == -1)
      errExit("lseek");

    numWritten = write(fd, "Test", sizeof("Test"));
    if (numWritten == -1)
      errExit("write");

    /*
    fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open64");

    off = atoll(argv[2]);
    if (lseek64(fd, off, SEEK_SET) == -1)
        errExit("lseek64");

    if (write(fd, "test", 4) == -1)
        errExit("write");
    */

    exit(EXIT_SUCCESS);
}
