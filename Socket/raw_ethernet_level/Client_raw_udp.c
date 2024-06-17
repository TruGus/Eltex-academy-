#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>
#include "function.h"


int main(){
  
  char buf[64]; // итоговый буфер c udp заголовком
  char ip_buf[84]; // буфер с ip заголовком
  char eth_buf[99];
  char recbuf[92]; // строка от сервера
  int flag = 1;

  uint16_t source_port = 8888;
  uint16_t destination_port = 7777;
  uint64_t dest_mac = 0x080027a0d6e3;//0x080027ee2486;
  
  //инициализация клиента и создание сокета
  struct sockaddr_in adr = {0};
  struct sockaddr_in adrclient = {0};
  struct sockaddr_ll serv = {0};

  int servfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if(servfd == -1){
    perror("socket");
  }

  /*if(setsockopt(servfd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof flag) == -1){
    perror("socket option");
  } */
  
  serv.sll_family = AF_PACKET;
  serv.sll_ifindex = if_nametoindex("wlo1");
  serv.sll_halen = 6;

  memcpy(serv.sll_addr, &dest_mac, 6);
 
  printf("mac adress\n");
  printf("%.x\n", serv.sll_addr[0]);
  printf("%.x\n", serv.sll_addr[1]);
  printf("%.x\n", serv.sll_addr[2]);
  printf("%.x\n", serv.sll_addr[3]);
  printf("%.x\n", serv.sll_addr[4]);
  printf("%.x\n", serv.sll_addr[5]);
 

  socklen_t socklen = sizeof(adr);

  int size_cl = sizeof(serv);
  int size = sizeof(adrclient);
  
  //создание udp загoловка 
  memcpy(buf, Create_UDP(), 13);

  //создание ip заголовка
  memcpy(ip_buf, Create_IP(buf), 33);

  //создание ethernet заголовка
  memcpy(eth_buf, Create_Ethernet(ip_buf), 47); //поменять размер
  
  //отправка пакета и получение ответа от сервера
  printf("Jn");
  if(sendto(servfd, eth_buf, 100,0,(struct sockaddr *) &serv, size_cl) == -1){
    perror("send");
  }

  printf("Jn");

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
