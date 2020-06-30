#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *term;
  char buf[200], var[200];
  if ((term = getenv("TERM")) == NULL) {
    printf("TERM variable not set, enter value: ");
    gets(buf);
    sprintf(var, "TERM=%s", buf);
    putenv(var);
    printf("%s\n", var);
  } else {
    printf("TERM=%s. Change? [y/N]", getenv("TERM"));
    gets(buf);
    if (buf[0] == 'Y' || buf[0] == 'y') {
      printf("TERM=");
      gets(buf);
      sprintf(var, "TERM=%s", buf);
      putenv(var);
      printf("new %s\n", var);
    }
  }
}
