#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "function.h"


int main(){

  char buf[64]; // итоговый буфер c udp заголовком
  char ip_buf[84]; // буфер с ip заголовком
  char recbuf[92]; // строка от сервера
  int flag = 1;

  uint16_t source_port = 8888;
  uint16_t destination_port = 7777;

  
  //инициализация клиента и создание сокета
  struct sockaddr_in adr = {0};
  struct sockaddr_in adrclient = {0};

  int servfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
  if(servfd == -1){
    perror("socket");
  }

  if(setsockopt(servfd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof flag) == -1){
    perror("socket option");
  } 

  adrclient.sin_family = AF_INET;
  adrclient.sin_port = htons(destination_port);
  adrclient.sin_addr.s_addr = INADDR_ANY;

  socklen_t socklen = sizeof(adr);

  int size_cl = sizeof(adrclient);
  int size = sizeof(adrclient);
  
  //создание udp загoловка 
  memcpy(buf, Create_UDP(), 64);

  //создание ip заголовка
  memcpy(ip_buf, Create_IP(buf), 84);

  //отправка пакета и получение ответа от сервера
  if(sendto(servfd, ip_buf,sizeof ip_buf + 1,0,(struct sockaddr *) &adrclient, size_cl) == -1){
    perror("send");
  }

  while(1){
    if(recvfrom(servfd, recbuf ,sizeof recbuf + 1,0,(struct sockaddr *) &adrclient,&size_cl) == -1){
      perror("recv");
    }
    if(htons(recbuf[21]) == 6100){
      printf("Зашел в условие\n");
      printf("%d\n", htons(recbuf[20])); //порт сервера
      printf("%d\n", htons(recbuf[21])); //порт сервера
    }
    if(htons(recbuf[20]) == 0x1e00){
    
      printf("Первый байт порта сервера - %.x\n", htons(recbuf[20])); // порт сервера
      printf("Второй байт порта сервера - %.x\n", htons(recbuf[21])); //порт сервера
      printf("%s\n", (recbuf + 28));
    }
  }
  close(servfd);
  return 0;
}
