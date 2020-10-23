#define MAXBUFF 80
#define PERM 0666
#define SERVER_BIN_NAME "03_08_shared_memory_server.bin"
#define PROJECT_ID 43

#include <sys/sem.h> // sembuf semaphore structure
#include <sys/shm.h> // shared memory

// define structure of shared memory
typedef struct mem_msg {
  int segment;
  char buff[MAXBUFF];
} Message;

// semaphore signal for client waiting processing
static struct sembuf proc_wait[1] = {
  1, -1, 0
};

// semaphore signal for client starting processing
static struct sembuf proc_start[1] = {
  1, 1, 0
};

// semaphore lock shared memory
static struct sembuf mem_lock[2] = {
  0, 0, 0,
  0, 1, 0
};

// semaphore free shared memory
static struct sembuf mem_unlock[1] = {
  0, -1, 0
};
