#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>

  struct client_data{
    struct sockaddr_in client;
    int client_descript;
  };

void *dop_serv(int*);

