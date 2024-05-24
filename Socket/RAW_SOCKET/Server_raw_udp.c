#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
  struct sockaddr_in adr;
  struct sockaddr_in adrclient;

  uint16_t port_number = 7777;

  int size_cl = sizeof(adrclient);
  int size = sizeof(adr);

  int servfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
  adr.sin_family = AF_INET;
  adr.sin_port = htons(port_number);
  socklen_t socklen = sizeof(adr);

  bind(servfd, (struct sockaddr *)&adr, socklen);

  char recbuf[64];
  while(1){
    recvfrom(servfd,recbuf,size,0,(struct sockaddr *) &adrclient,&size_cl);
    printf("Я получил пакет\n");
  }

  close(servfd);
  return 0;
}
