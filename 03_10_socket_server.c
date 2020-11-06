#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> // socketaddr_un type
#define MAXBUFF 256
#define SOCKET_FILE "./03_10_socket_server.sock"

#include <unistd.h>
#include <stdlib.h> // for exit()
#include <stdio.h> // for print
#include <errno.h> // for strerror
#include <string.h> // for strerror

int main() {
  char buf[MAXBUFF];
  struct sockaddr_un serv_addr, clnt_addr;
  socklen_t saddrlen, caddrlen;
  int sockfd;
  int max_caddrlen, n;

  // create socket
  if ((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
    printf("Creating socket error\n"); exit(1);
  }

  // delete socket file if it exists and bind socket to local address
  unlink(SOCKET_FILE);
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sun_family = AF_UNIX;
  strcpy(serv_addr.sun_path, SOCKET_FILE);
  saddrlen = sizeof(serv_addr.sun_family) + strlen(serv_addr.sun_path);

  if (bind(sockfd, (struct sockaddr *)&serv_addr, saddrlen) < 0) {
    printf("Bind socket failed\n"); exit(1);
  }

  // reading from socket in loop
  max_caddrlen = sizeof(clnt_addr);

  for (;;) {
    caddrlen = max_caddrlen;
    n = recvfrom(sockfd, buf, MAXBUFF, 0, (struct sockaddr *)&clnt_addr, &caddrlen);
    if (n < 0) {
      printf("Receiving message from client error\n"); exit(1);
    }
    // return received message to client
    if (sendto(sockfd, buf, n, 0, (struct sockaddr *)&clnt_addr, caddrlen) != n) {
      printf("Send message to client error\n"); exit(1);
    }
  }

  exit(0);
}
