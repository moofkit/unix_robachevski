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

void timer(int delay, int count_limit) {
  time_t rawtime;
  struct tm * timeinfo;

  for(int count = 0; count < count_limit; ++count) {
    sleep(delay);
    syslog(LOG_INFO, "Current local time and date: %s", asctime (timeinfo));
  }
}

int main(int argc, char **argv) {
  int fd;
  struct rlimit rlim;

  // ignore stdin and stdout signals if daemon is not running by init
  if (getpid() != 1) {
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
  }

  // make a child process
  if (fork() == 0) {
    exit(0); // exit from parent process
    setsid(); // make child process group leader
  }

  // close file descriptors: stdout, stderr
  getrlimit(RLIMIT_NOFILE, &rlim);
  for (fd = 0; fd < rlim.rlim_max; fd++) {
    close(fd);
  }

  // change dir to root
  chdir("/");
  // syslog registration
  openlog("Useful daemon", LOG_PID | LOG_CONS, LOG_DAEMON);
  syslog(LOG_INFO, "Starting daemon...");

  timer(5, 100);
  closelog();
}
