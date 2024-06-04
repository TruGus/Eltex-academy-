#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT_NUM 7777

int main(){
  struct sockaddr_in adr = {0};
  struct sockaddr_in adrclient = {0};
  int size, size_cl;
  char sendbuf[64] = " :from server";
  char recbuf[64];

  int servfd = socket(AF_INET, SOCK_DGRAM, 0);
  adr.sin_family = AF_INET;
  adr.sin_port = htons(PORT_NUM);
  socklen_t socklen = sizeof(adr);
  size_cl = sizeof(adrclient);

  bind(servfd, (struct sockaddr *)&adr, socklen);
  size = sizeof(adr);
  printf("Ожидание пакетов от клиента\n");
  int recsize = 0;
  
  //получение пакета от клиента и модификация строки
  if(recsize = recvfrom(servfd,recbuf,sizeof recbuf + 1,0,(struct sockaddr *) &adrclient,&size_cl) == -1){
    perror("recv");
  }

  printf("Порт сервера - %d\n", adr.sin_port);

  strncat(recbuf, sendbuf, 30);
  printf("%d\n", adrclient.sin_port);

  if(sendto(servfd,recbuf,sizeof recbuf,0,(struct sockaddr *) &adrclient, size_cl) == -1){
    perror("send");
  }
 
  printf("%s\n", recbuf);
  sleep(1);

  close(servfd);
  return 0;
}
