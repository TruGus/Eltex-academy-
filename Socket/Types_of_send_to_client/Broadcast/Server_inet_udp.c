#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

uint16_t port_number = 7777;


int main(){
  struct sockaddr_in adrclient = {0};
  struct in_addr ip_address;
  int size, size_cl;
  char sendbuf[64] = "Hello";
  char recbuf[64];
  
  int flag = 1;

  int servfd = socket(AF_INET, SOCK_DGRAM, 0);
  int ret_s = setsockopt(servfd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof flag);
  if(ret_s == -1){
    perror("sockopt");
  }
  

  adrclient.sin_family = AF_INET;
  adrclient.sin_port = htons(port_number);
  adrclient.sin_addr.s_addr = INADDR_BROADCAST;
    
  size_cl = sizeof(adrclient);

  size = sizeof(adrclient);
  
  while(1){
    int ret = sendto(servfd,sendbuf,sizeof sendbuf,0,(struct sockaddr *) &adrclient, size_cl);
    if(ret == -1){
      perror("send");
      printf("pf,bd");
    }

    sleep(3);
  }


  close(servfd);
  return 0;
}
