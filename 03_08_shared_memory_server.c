#include <sys/types.h>
#include <sys/ipc.h>
#include "03_07_shared_memory.h"
#include <unistd.h>
#include <stdlib.h> // for exit()
#include <stdio.h> // for print
#include <errno.h> // for strerror
#include <string.h> // for strerror

int main() {
  Message *msgptr;
  key_t key;
  int shmid, semid;

  // get key by server file path and project identifier
  if ((key = ftok(SERVER_BIN_NAME, PROJECT_ID)) < 0) {
    printf("Get key error\n"); exit(1);
  }
  // allocate shared memory
  if ((shmid = shmget(key, sizeof(Message), PERM | IPC_CREAT)) < 0) {
    printf("Allocating shared memory failed\n"); exit(1);
  }
  // Attaching shared memory
  if ((msgptr = (Message *)shmat(shmid, 0, 0)) < 0) {
    printf("Attaching shared memory failed\n"); exit(1);
  }
  // create 2 semaphores
  // first - sync client/server processing
  // second - sync shared memory access
  if ((semid = semget(key, 2, PERM | IPC_CREAT)) < 0) {
    printf("Creating semaphore failed\n"); exit(1);
  }

  // Waiting for client lock shared memory
  if (semop(semid, &proc_wait[0], 1) < 0) {
    printf("Waiting for client lock shared memory failed\n"); exit(1);
  }

  // Waiting for client finishing processing and lock shared memory
  if (semop(semid, &mem_lock[0], 2) < 0) {
    printf("Waiting for client to finish processing failed%s\n", strerror(errno)); exit(1);
  }

  // print message form shared memory
  printf("%s", msgptr->buff);

  // unlock shared memory
  if (semop(semid, &mem_unlock[0], 2) < 0) {
    printf("Unlock shared memory failed\n"); exit(1);
  }
  // detach shared memory
  if (shmdt(msgptr) < 0) {
    printf("Detach shared memory failed\n"); exit(1);
  }
  exit(0);
}
