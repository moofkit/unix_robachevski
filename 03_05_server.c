#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "03_04_mesg.h"
#include <unistd.h>
#include <stdlib.h> // for exit()
#include <stdio.h> // for print
#include <errno.h> // for strerror

int main() {
  Message message; // our message struct
  key_t key;
  int msgid, length, n;

  // get key by server file path and project identifier
  if ((key = ftok(SERVER_BIN_NAME, PROJECT_ID)) < 0) {
    printf("Get key error\n"); exit(1);
  }

  // type of recieving messages
  message.mtype = 1L;
  // create message queue
  if ((msgid = msgget(key, PERM | IPC_CREAT)) < 0) {
    printf("Creating queue error\n"); exit(1);
  }
  // read message from queue
  n = msgrcv(msgid, &message, sizeof(message), message.mtype, 0);
  // send message to stdout
  if (n > 0) {
    if (write(1, message.buff, n) != n) {
      printf("Output error\n"); exit(1);
    }
  } else { printf("Read message error%s\n", strerror(errno)); exit(1); }

  exit(0);
}
