#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO "fifo.1"

int main()
{
  int writefd, n;
  // open fifo file with write permissions
  if ((writefd = open(FIFO, O_WRONLY)) < 0) {
    printf("Open file error\n"); exit(1);
  }
  // write message to fifo file
  if (write(writefd, "Hello, world!\n", 15) != 15) {
    printf("Write error\n"); exit(1);
  }
  // close fifo file
  close(writefd);
  // delete fifo file
  if (unlink(FIFO) < 0) {
    printf("Error deleting FIFO file\n"); exit(1);
  }

  exit(0);
}
