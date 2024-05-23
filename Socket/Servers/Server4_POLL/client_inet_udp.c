#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "function.h"

int default_port = 7777;

int main(){

  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  char sendbuf[64] = "Client";
  char sendbuf_2[64] = "Client try to connect";
  char recbuf[64];
  int port_number = 0;
  int serv_number = 0;
  int time[3];
  int message_number = 0;
  struct sockaddr_in adr = {0};
  adr.sin_family = AF_INET;
  adr.sin_port = htons(default_port);
  int size = sizeof(adr);
  int con = connect(fd, (struct sockaddr *) &adr, size);
  if(con == -1){
    perror("con");
  }
  else{
    printf("Подключение выполнено\n");
  }

  send(fd,sendbuf_2,sizeof(sendbuf_2), 0); 

  int r = recv(fd, time, sizeof time, 0);
  if(r == -1){
    perror("recv");
  }
  
  printf("Time %d:%d:%d\n", time[0], time[1], time[2]);;

  close(fd);
  return 0;
}
