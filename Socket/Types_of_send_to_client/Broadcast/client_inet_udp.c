#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

uint16_t port_number = 7777;

int main(){
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(fd == -1){
    perror("Socket");
  }
  char recbuf[64];

  struct sockaddr_in adr = {0};

  adr.sin_family = AF_INET;
  adr.sin_port = htons(port_number);
  adr.sin_addr.s_addr = inet_addr("255.255.255.255");

 
  int size_cl = sizeof(adr);
  socklen_t socklen = sizeof(adr);

  int ret_b = bind(fd, (struct sockaddr *)&adr, socklen);
  if(ret_b == -1){
    perror("bind");
  }

  int ret = recvfrom(fd, recbuf, sizeof recbuf, 0, (struct sockaddr *)&adr, &socklen);
  if(ret == -1){
    perror("recv");
  }
  else{
    printf("Посылка принята\n");
  }

  printf("%s\n", recbuf);

  close(fd);
  return 0;
}
