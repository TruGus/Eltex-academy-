#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int main(){
  struct udp_header{
    unsigned short source_port;
    unsigned short destination_port;
    unsigned short len;
    unsigned short checksum;
  };

  char buf[64]; // итоговый буфер
  char recbuf[92]; // строка от сервера
 
  struct udp_header *datagram = (struct udp_header* ) buf;

  uint16_t source_port = 8888;
  uint16_t destination_port = 7777;
  
  char *payload = "Help";

  struct sockaddr_in adr = {0};
  struct sockaddr_in adrclient = {0};

  //инициализация клиента и создание сокета
  int servfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
  if(servfd == -1){
    perror("socket");
  }

  adrclient.sin_family = AF_INET;
  adrclient.sin_port = htons(destination_port);
  adrclient.sin_addr.s_addr = INADDR_ANY;

  socklen_t socklen = sizeof(adr);

  int size_cl = sizeof(adrclient);
  int size = sizeof(adrclient);
  
  //заполнение самой датаграммы
  datagram->source_port = htons(source_port);
  datagram->destination_port = htons(destination_port);
  datagram->len = strlen(payload) + sizeof datagram;
  datagram->len = htons(datagram->len);
  datagram->checksum = 0;
  
  memcpy(buf + 8, payload, 5);

  //вывод датаграммы побайтно в little-endian
  printf("%.2x - порт источника\n", datagram->source_port);
  printf("%.2x - порт назначения\n", datagram->destination_port);
  printf("%.4x - длина\n", datagram->len);
  printf("%.2x - чексумма\n", datagram->checksum);

  //отправка пакета и получение ответа от сервера
  if(sendto(servfd,buf,sizeof datagram + sizeof payload,0,(struct sockaddr *) &adrclient, size_cl) == -1){
    perror("send");
  }

  while(1){
    if(recvfrom(servfd, recbuf ,sizeof recbuf + 1,0,(struct sockaddr *) &adrclient,&size_cl) == -1){
      perror("recv");
    }
    if(htons(recbuf[21]) == 6100){
      printf("Зашел в условие\n");
      printf("%d\n", htons(recbuf[20])); // порт сервера
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
