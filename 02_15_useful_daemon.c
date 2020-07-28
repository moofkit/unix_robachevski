#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

void ticker(int delay, int count_limit) {
  time_t rawtime;
  struct tm * timeinfo;

  for(int count = 0; count < count_limit; ++count) {
    sleep(delay);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    syslog(LOG_INFO, "Current local time and date: %s", asctime(timeinfo));
  }
}

int main(int argc, char **argv) {
  pid_t pid;

  // make a child process
  pid = fork();

  // error occurred
  if (pid < 0)
    exit(EXIT_FAILURE);

  // terminate parent on succes fork
  if (pid > 0)
    exit(EXIT_SUCCESS);

  // make child process group leader
  if (setsid() < 0)
    exit(EXIT_FAILURE);

  // ignore stdin and stdout signals if daemon is not running by init
  signal(SIGTTOU, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);

  // fork one more time
  pid = fork();
  if (pid < 0)
    exit(EXIT_FAILURE);
  if (pid > 0)
    exit(EXIT_SUCCESS);

  // set new file permissions
  umask(0);

  // change dir to root
  chdir("/");

  int fd;
  // close file descriptors: stdout, stderr
  for (fd = sysconf(_SC_OPEN_MAX); fd>=0; fd--) {
    close(fd);
  }

  // syslog registration
  openlog("Useful daemon", LOG_PID | LOG_CONS, LOG_DAEMON);
  syslog(LOG_INFO, "Starting daemon...");

  while(true) {
    ticker(1, 5); // hard work
    break;
  }
  syslog(LOG_INFO, "Daemon terminated.");
  closelog();
}
