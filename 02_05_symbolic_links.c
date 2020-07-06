#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> // readline, close, read

#define BUFSIZE 256

int main(int argc, char *argv[]) {
  char buf[BUFSIZE + 1];
  int nread, fd;

  printf("Reading symbolic link\n");
  nread = readlink(argv[1], buf, BUFSIZE);
  if (nread < 0) {
    perror("readlink");
    exit(1);
  }

  // readlink does not complete line with \0 so we did it manually
  buf[nread] = '\0';
  printf("Symbolic link content:\n %s\n", buf);

  printf("Reading target file...\n");
  fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    perror("open");
    exit(2);
  }
  nread = read(fd, buf, BUFSIZE);
  if (nread < 0) {
    perror("read");
    exit(3);
  }

  buf[nread] = '\0';
  printf("Target file content:\n %s\n", buf);
  close(fd);
  exit(0);
}
