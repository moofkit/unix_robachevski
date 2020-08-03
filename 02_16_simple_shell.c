#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char ** environ;
#define CMDSIZE 128;
// integreted shell commands
#define UNKNOWN 0
#define CD 1
#define ECHO 2
#define EXEC 3
#define PROGRAM 1000

int parse_command(char *cmdbuf, char *path, char **arguments) {
  // TODO: split cmdbuf with spaces to command path and arguments
  char command;
  int command_code;

  if (command == 'cd') {
    command_code = CD;
  } else if (command == 'echo') {
    command_code =  ECHO;
  } else if (command == 'exec') {
    command_code = EXEC;
  } else {
    command_code = PROGRAM;
  }

  return command_code;
}
