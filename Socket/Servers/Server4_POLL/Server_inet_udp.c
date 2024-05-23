#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "function.h"
#include <time.h>
#include <sys/poll.h>

uint16_t port_number_udp = 7777; //порт сервера udp
uint16_t port_number_tcp = 7778; //порт сервера tcp

int main(){

  struct pollfd fds[2];
  int ret;

  fds[0].fd = 0;
  fds[0].events = POLLIN;

  fds[1].fd = 1;
  fds[1].events = POLLIN;
  

  //создание двух серверов
  struct sockaddr_in adr, adr_tcp;
  struct sockaddr_in adrclient, adrclient_tcp;
  int size, size_cl;
  char recbuf[64];
  
  size_cl = sizeof(adrclient);
  size = sizeof(adr);

  int test[3]; 
  time_t mytime;
  struct tm *now;

  fds[0].fd = socket(AF_INET, SOCK_DGRAM, 0);
  adr.sin_family = AF_INET;
  adr.sin_port = htons(port_number_udp);
  socklen_t socklen = sizeof(adr);
  
  bind(fds[0].fd, (struct sockaddr *)&adr, socklen);
  //тут нужно подключить еще и tcp сокет

  fds[1].fd = socket(AF_INET, SOCK_STREAM, 0);
  adr_tcp.sin_family = AF_INET;
  adr_tcp.sin_port = htons(port_number_tcp);
  socklen_t adrlen = sizeof (adr_tcp);
  int clientfd;
  bind(fds[1].fd, (struct sockaddr *)&adr_tcp, sizeof(adr_tcp));
  listen(fds[1].fd, 1);

while(1){
    ret = poll(fds, 2, 5 * 1000);
  if(!ret){
    printf("TIMEOUT\n");
  } 
  else{
    if(fds[0].revents & POLLIN){
      printf("Подключился клиент UDP\n");
      recvfrom(fds[0].fd,recbuf,size,0,(struct sockaddr *) &adrclient,&size_cl);
      printf("%s\n", recbuf);

      time(&mytime);
      now = localtime(&mytime);
      test[0] = now->tm_hour;
      test[1] = now->tm_min;
      test[2] = now->tm_sec;

      printf("Time %d:%d:%d\n", test[0], test[1], test[2]);
      sendto(fds[0].fd,test,size,0,(struct sockaddr *) &adrclient, size_cl);
    }

    if(fds[1].revents & POLLIN){
      clientfd = accept(fds[1].fd, (struct sockaddr *) &adrclient_tcp, &adrlen);
      if(clientfd == -1){
        perror("client");
      }
      printf("Подключился клиент tcp\n");
      recv(fds[1].fd, recbuf, sizeof recbuf, 0);
      printf("%s\n", recbuf);

      time(&mytime);
      now = localtime(&mytime);
      test[0] = now->tm_hour;
      test[1] = now->tm_min;
      test[2] = now->tm_sec;

      printf("Time %d:%d:%d\n", test[0], test[1], test[2]);
      send(clientfd, test, sizeof (test), 0);
    }
  }
}

  close(clientfd);
  close(fds[0].fd);
  close(fds[1].fd);

  return 0;
}

   
   