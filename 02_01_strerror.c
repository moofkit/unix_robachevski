#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  fprintf(stderr, "ENOMEM: %s\n", strerror(ENOMEM));
  errno = ENOEXEC;
  perror(argv[0]);
}
