#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
main()
{
  int fd;
  char buf[80];
  fd = open("01_introduction_file_open.c", O_RDONLY);
  read(fd, buf, sizeof(buf));
  close(fd);
  printf("Done!\n");
}
