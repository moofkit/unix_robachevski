#include <sys/types.h>
#include <sys/ipc.h>
#include "03_07_shared_memory.h"
#include <unistd.h>
#include <stdlib.h> // for exit()
#include <stdio.h> // for print
#include <errno.h> // for strerror

int main() {
  Message *msgptr;
  key_t key;
  int shmid, semid;

  // get key by server file path and project identifier
  if ((key = ftok(SERVER_BIN_NAME, PROJECT_ID)) < 0) {
    printf("Get key error\n"); exit(1);
  }

  // get access to shared memory
  if ((shmid = shmget(key, sizeof(Message), 0)) < 0) {
    printf("Access shared memory error\n"); exit(1);
  }

  // attach shared memory
  if ((msgptr = (Message *) shmat(shmid, 0, 0)) < 0) {
    printf("Attach shared memory error\n"); exit(1);
  }

  // get semaphore
  if ((semid = semget(key, 2, PERM)) < 0) {
    printf("Shared memory semaphore error\n"); exit(1);
  }
  // lock shared memory
  if (semop(semid, &mem_lock[0], 2) < 0) {
    printf("Lock shared memory error\n"); exit(1);
  }
  // sent message to server about start work
  if (semop(semid, &proc_start[0], 1) < 0) {
    printf("Client/server semaphore error\n"); exit(1);
  }
  // write message to shared memory
  sprintf(msgptr->buff, "Hello World!\n");
  // unlock shared memory
  if (semop(semid, &mem_unlock[0], 2) < 0) {
    printf("Unlock shared memory error\n"); exit(1);
  }
  // waiting for server done his job
  if (semop(semid, &mem_lock[0], 2) < 0) {
    printf("Server memory unlock error\n"); exit(1);
  }
  // detach shared memory
  if (shmdt(msgptr) < 0) {
    printf("Shared memory detach error\n"); exit(1);
  }
  // delete IPC objects - semaphore and shared memory
  if (shmctl(shmid, IPC_RMID, 0) < 0) {
    printf("Shared memory delete error\n"); exit(1);
  }
  if (semctl(semid, 0, IPC_RMID) < 0) {
    printf("Semaphore delete error\n"); exit(1);
  }
  exit(0);
}
