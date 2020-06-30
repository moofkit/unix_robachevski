#include <stddef.h>
#include <stdio.h>
extern char **environ;

int main(int argc, char *argv[]) {
  int i;
  printf("numbers of arguments passed to program %s equal to %d\n", argv[0], argc - 1);
  for (i = 1; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  for (i = 0; i < 8; i++) {
    if (environ[i] != NULL) {
      printf("environ[%d] : %s\n", i, environ[i]);
    }
  }
}
