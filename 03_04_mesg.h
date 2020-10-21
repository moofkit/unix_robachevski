#define MAXBUFF 80
#define PERM 0666
#define SERVER_BIN_NAME "03_05_server.bin"
#define PROJECT_ID 42

// define structure of message
// the only required field is mtype
// buff is optional and used to store the message itself
typedef struct our_msgbuf {
  long mtype;
  char buff[MAXBUFF];
} Message;
