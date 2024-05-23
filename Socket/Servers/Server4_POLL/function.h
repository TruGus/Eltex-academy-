#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <malloc.h>

#define SERV_NUMBER 2 // количество вспомогательных серверов
#define MSG_COUNT 2 // размер очереди заявок

   struct msgbuf{
    int msg_buf[MSG_COUNT]; //очередь заявок
    int server_lock[SERV_NUMBER]; //блокировка серверов значения 0 и 1
    int all_server_lock;// блокировка всех серверов значения 0 и 1
  };

void *dop_serv(int*);

