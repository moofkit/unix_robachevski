#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *term;
  char buf[200], var[200];
  term = getenv("TERM");
  if (term == NULL) {
    printf("TERM variable not set, enter value: ");
    gets(buf);
    sprintf(var, "TERM=%s", buf);
    putenv(var);
    printf("%s\n", var);
  } else {
    printf("TERM=%s. Change? [y/N]", term);
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
