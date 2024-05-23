#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "function.h"

uint16_t default_port = 7778;

int main(){
  //создание сокета клиента и установление соединения
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in adr = {0};

  adr.sin_family = AF_INET;
  adr.sin_port = htons(default_port);
 
  int con = connect(fd, (struct sockaddr *) &adr, sizeof adr);

  if(con == -1){
    perror("con");
  }
  printf("Подключение выполнено\n");
  //printf("Time %d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec);

  char sendbuf[64] = "Запрашиваю текущее время";
  char recbuf[128];
  int time[3];
  int r1 = send(fd, sendbuf, sizeof sendbuf, 0);
  if(r1 == -1){
    perror("send");
  }
  sleep(5);

  int r = recv(fd, time, sizeof time, 0);
  if(r == -1){
    perror("recv");
  }
  printf("Time %d:%d:%d\n", time[0], time[1], time[2]);

  close(fd);
  return 0;
}
