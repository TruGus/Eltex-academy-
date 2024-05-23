#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>

#define SERV_NUMBER 2 // количество доп серверов

   struct msgbuf{
    int server_lock[SERV_NUMBER]; //блокировка серверов значения 0 и 1
    int all_server_lock;// блокировка всех серверов значения 0 и 1
  };

void *dop_serv(int*);

