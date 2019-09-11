#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>


#include "QueryProtocol.h"
#include "MovieSet.h"
#include "MovieIndex.h"
#include "DocIdMap.h"
#include "htll/Hashtable.h"
#include "QueryProcessor.h"
#include "FileParser.h"
#include "FileCrawler.h"

DocIdMap docs;
Index docIndex;

#define BUFFER_SIZE 1000
#define SEARCH_RESULT_LENGTH 1500
char movieSearchResult[SEARCH_RESULT_LENGTH];

int Cleanup();

void sigint_handler(int sig) {
  write(0, "Exit signal sent. Cleaning up...\n", 34);
  Cleanup();
  exit(0);
}

int CheckACK(int sock_fd) {
  char resp[BUFFER_SIZE];
  int len = read(sock_fd, resp, BUFFER_SIZE - 1);
  resp[len] = '\0';
  return CheckAck(resp);
}

void Setup(char *dir) {
  printf("Crawling directory tree starting at: %s\n", dir);
  // Create a DocIdMap
  docs = CreateDocIdMap();
  CrawlFilesToMap(dir, docs);
  printf("Crawled %d files.\n", NumElemsInHashtable(docs));

  // Create the index
  docIndex = CreateIndex();

  // Index the files
  printf("Parsing and indexing files...\n");
  ParseTheFiles(docs, docIndex);
  printf("%d entries in the index.\n", NumElemsInHashtable(docIndex->ht));
}

int Cleanup() {
  DestroyOffsetIndex(docIndex);
  DestroyDocIdMap(docs);

  return 0;
}

void GetRes(int client_fd, char *buffer) {
  SearchResultIter iter  = FindMovies(docIndex, buffer);
  int res_num = NumResultsInIter(iter);
  printf("number of result for term \"%s\" : %d\n", buffer, res_num);
  char res_str[1000];
  sprintf(res_str, "%d", res_num);
  write(client_fd, res_str, strlen(res_str));
  if (CheckACK(client_fd) == -1) {
    return;
  }
  char temp[1000];

  if (iter == NULL) {
    printf("No results for this term. Please try another.\n");
  } else {
    SearchResult sr = (SearchResult)malloc(sizeof(*sr));
    if (sr == NULL) {
      printf("Couldn't malloc SearchResult\n");
    } else {
      while (res_num > 0) {
        SearchResultGet(iter, sr);
        CopyRowFromFile(sr, docs, temp);
        write(client_fd, temp, strlen(temp));
        if (CheckACK(client_fd) == -1) {
          return;
        }
        res_num--;
        SearchResultNext(iter);
      }
    }
    free(sr);
  }
  printf("Destroying search result iter\n");
  DestroySearchResultIter(iter);
}

int main(int argc, char **argv) {
  // Get args
  if (argc != 3) {
    printf("please run server as \"./queryserver [datadir] [port]\"\n");
    return 0;
  }

  char *dir_to_crawl = argv[1];
  char *port = argv[2];
  // Setup graceful exit
  struct sigaction kill;

  kill.sa_handler = sigint_handler;
  kill.sa_flags = 0;  // or SA_RESTART
  sigemptyset(&kill.sa_mask);

  if (sigaction(SIGINT, &kill, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  Setup(dir_to_crawl);

  // Step 1: get address/port info to open
  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int s = getaddrinfo("localhost", port, &hints, &res);
  if (s != 0) {
    fprintf(stderr, "get address info: %s\n", gai_strerror(s));
    exit(1);
  }

  // Step 2: Open socket
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  // Step 3: Bind socket
  if (bind(sock_fd, res->ai_addr, res->ai_addrlen) != 0) {
    perror("bind()");
    exit(1);
  }

  // Step 4: Listen on the socket
  if (listen(sock_fd, 10) != 0) {
    perror("listen()");
    exit(1);
  }

  // Step 5: Handle clients that connect
  struct sockaddr_in *result_addr = (struct sockaddr_in *) res->ai_addr;
  printf("Listening on file descriptor %d, port %d\n",
          sock_fd, ntohs(result_addr->sin_port));

  while (1) {
    printf("Waiting for connection...\n");
    int client_fd = accept(sock_fd, NULL, NULL);
    printf("Connection made: client_fd=%d\n", client_fd);
    printf("Send ACK\n");
    SendAck(client_fd);

    char buffer[1000];
    int len = read(client_fd, buffer, sizeof(buffer) - 1);
    buffer[len] = '\0';
    printf("Read %d chars\n", len);
    printf("===\n");
    printf("received query: %s \n", buffer);

    GetRes(client_fd, buffer);
    // CheckAck
    SendGoodbye(client_fd);

    // Step 6: Close the socket
    close(client_fd);
    printf("client disconnected\n");
  }

  // Got Kill signal
  close(sock_fd);

  Cleanup();

  return 0;
}
