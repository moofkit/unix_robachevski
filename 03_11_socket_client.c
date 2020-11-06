#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> // socketaddr_un type
#define MAXBUFF 256
#define SOCKET_FILE "./03_10_socket_server.sock"

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h> // for exit()
#include <stdio.h> // for print
#include <errno.h> // for strerror
#include <string.h> // for strerror

int main() {
  char buf[MAXBUFF];
  char *msg = "Hello World!\n";

  struct sockaddr_un serv_addr, clnt_addr;
  int sockfd;
  socklen_t saddrlen, caddrlen;
  int n;
  int msglen = strlen(msg);

  // setup socket address
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sun_family = AF_UNIX;
  strcpy(serv_addr.sun_path, SOCKET_FILE);
  saddrlen = sizeof(serv_addr.sun_family) + strlen(serv_addr.sun_path);
  // create datagram socket
  if ((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
    printf("Creating socket error\n"); exit(1);
  }

  // to recive message back from server it needs to create client uniq addres
  // using mktemp function for creating temp file that will be as uniq identifier
  bzero(&clnt_addr, sizeof(clnt_addr));
  clnt_addr.sun_family = AF_UNIX;
  strcpy(clnt_addr.sun_path, "/tmp/03_11_socket_client.XXXX");
  mktemp(clnt_addr.sun_path);
  caddrlen = sizeof(clnt_addr.sun_family) + strlen(clnt_addr.sun_path);

  if (bind(sockfd, (struct sockaddr *)&clnt_addr, caddrlen) < 0) {
    printf("Socket bind error\n"); exit(1);
  }

  // send message to server
  if (sendto(sockfd, msg, msglen, 0, (struct sockaddr *)&serv_addr, saddrlen) < 0) {
    printf("Send message error\n"); exit(1);
  }

  // receive response from server
  if (recvfrom(sockfd, buf, MAXBUFF, 0, NULL, 0) < 0) {
    printf("Receive message error\n"); exit(1);
  }

  printf("Echo: %s\n", buf);
  // clean up
  close(sockfd);
  unlink(clnt_addr.sun_path);
  exit(0);
}
