#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define FIFO "fifo.1"
#define MAXBUFF 80

int  main()
{
  int readfd, n;
  char buff[MAXBUFF];

  // Create fifo file with permissions for all
  if (mknod(FIFO, S_IFIFO | 0666, 0) < 0) {
    printf("Error creating fifo file: %s\n", strerror(errno)); exit(1);
  }
  // Read fifo file
  if ((readfd = open(FIFO, O_RDONLY)) < 0) {
    printf("Error opening fifo file\n"); exit(1);
  }
  // Read message from fifo file
  while ((n = read(readfd, buff, MAXBUFF)) >0)
    if (write(1, buff, n) != n) {
      printf("Output error\n"); exit(1);
    }
  // Close fifo file
  close(readfd);
  exit(0);
}
