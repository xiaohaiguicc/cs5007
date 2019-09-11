#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "includes/QueryProtocol.h"
// #include "QueryClient.h"

char *port_string = "1500";
unsigned short int port;
char *ip = "127.0.0.1";

#define BUFFER_SIZE 1000

int CheckACK(int sock_fd) {
  char resp[BUFFER_SIZE];
  int len = read(sock_fd, resp, BUFFER_SIZE - 1);
  resp[len] = '\0';
  return CheckAck(resp);
}

int GetResponseNum(int sock_fd) {
  char resp[BUFFER_SIZE];
  int len = read(sock_fd, resp, BUFFER_SIZE - 1);
  resp[len] = '\0';
  int respNum = atoi(resp);
  printf("number of responses : %d\n", respNum);
  return respNum;
}

void GetResponse(int sock_fd) {
  char resp[BUFFER_SIZE];
  int len = read(sock_fd, resp, BUFFER_SIZE - 1);
  resp[len] = '\0';
  printf("response is %s\n", resp);
}

void RunQuery(char *query) {
  int sock_fd, s;
  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  // Find the address
  s = getaddrinfo(ip, port_string, &hints, &res);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(1);
  }

  // Create the socket
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    printf("Socket Error");
  } else {
    printf("Socket opened\n");
  }

  // Connect to the server
  if (connect(sock_fd, res->ai_addr, res->ai_addrlen) == -1) {
    perror("connect");
    exit(2);
  } else {
    printf("Connection to movie server\n");
  }

  if (CheckACK(sock_fd) == -1) {
    return;
  }

  // Do the query-protocol
  write(sock_fd, query, strlen(query));
  int resp_num = GetResponseNum(sock_fd);
  SendAck(sock_fd);

  for (int i = 0; i < resp_num; i++) {
    GetResponse(sock_fd);
    SendAck(sock_fd);
  }
  GetResponse(sock_fd);
  SendAck(sock_fd);

  char resp[BUFFER_SIZE];
  int len = read(sock_fd, resp, BUFFER_SIZE - 1);
  resp[len] = '\0';
  CheckGoodbye(resp);
  // Close the connection
  freeaddrinfo(res);
  close(sock_fd);
}

void RunPrompt() {
  char input[BUFFER_SIZE];

  while (1) {
    printf("Enter a term to search for, or q to quit: ");
    scanf("%s", input);

    printf("input was: %s\n", input);

    if (strlen(input) == 1) {
      if (input[0] == 'q') {
        printf("Thanks for playing! \n");
        return;
      }
    }
    printf("\n\n");
    RunQuery(input);
  }
}

int main(int argc, char **argv) {
  // Check/get arguments
  if (argc != 3) {
    fprintf(stderr, "Pleas use format \"queryclient [ipaddress] [port]\"\n");
    return 1;
  }

  // Get info from user
  if (strcmp(argv[1], "localhost") != 0) {
    ip = argv[1];
  }
  port_string = argv[2];

  // Run Query
  RunPrompt();
  return 0;
}
