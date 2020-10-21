#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "03_04_mesg.h"
#include <unistd.h>
#include <stdlib.h> // for exit()
#include <stdio.h> // for print

int main() {
  Message message; // our message struct
  key_t key;
  int msgid, length, n;

  // get key
  if ((key = ftok(SERVER_BIN_NAME, PROJECT_ID)) < 0) {
    printf("Get key error\n"); exit(1);
  }

  // type of sending messages
  message.mtype = 1L;
  if ((msgid = msgget(key, 0)) < 0) {
    printf("Message queue access error\n"); exit(1);
  }
  // write message to queue
  if ((length = sprintf(message.buff, "Hello world!\n")) < 0) {
    printf("Copy to buffer error\n"); exit(1);
  }
  // send message to queue
  if (msgsnd(msgid, (void *) &message, length, 0) < 0) {
    printf("Send message error\n"); exit(1);
  }
  // delete queue
  if (msgctl(msgid, IPC_RMID, 0) < 0) {
    printf("Delete queue error\n"); exit(1);
  }
  exit(0);
}
