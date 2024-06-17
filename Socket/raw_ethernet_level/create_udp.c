#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "function.h"

char buf[13]; // итоговый буфер

char* Create_UDP(){
  
  char *payload = "Help";

  uint16_t source_port = htons(8888);
  uint16_t destination_port = htons(7777);
  uint16_t len = htons(strlen(payload) + 8);
  uint16_t checksum = 0;

  //заполнение датаграммы
  memcpy(buf, &source_port, 2);
  memcpy(buf + 2, &destination_port, 2);
  memcpy(buf + 4, &len, 2);
  memcpy(buf + 6, &checksum, 2);
  memcpy(buf + 8, payload, 5);


  //вывод датаграммы 
  printf("UDP заголовок\n");
  printf("%.2x - порт источника\n", htons(source_port));
  printf("%.2x - порт назначения\n", htons(destination_port));
  printf("%.2x - длина\n", htons(len));
  printf("%.2x - чексумма\n", htons(checksum));
  printf("\n");

  return buf;
}