#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "function.h"

int default_port = 7777;

int main(){

  char* path = "bin";
  struct msgbuf *memory;
  __key_t key = ftok(path, 1);
  __key_t key_for_sem = ftok(path, 2);
  int msg = shmget(key, 1, 0);
  int sem = semget(key_for_sem, 1, 0);

  memory = (struct msgbuf *) shmat(msg, 0, 0666);

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

  
  printf("Прием нового порта и номера сервера\n");
  int s = send(fd,sendbuf_2,sizeof(sendbuf_2), 0); // отправка данных для основного сервера
  int ret = recv(fd, &message_number, sizeof message_number,0);
  if(ret == -1){
    perror("recv");
  }
  printf("Ваша заявку обрабатывает сервер %d \n", message_number);
  message_number++;
  message_number = message_number + default_port;
  printf("Новый порт для подключения - %d\n", message_number);

  adr.sin_family = AF_INET;
  adr.sin_port = htons(message_number);
  size = sizeof(adr);

  con = connect(fd, (struct sockaddr *) &adr, size);
  if(con == -1){
    perror("con");
  }
  else{
    printf("Подключение выполнено\n");
  }

  send(fd,sendbuf_2,sizeof(sendbuf_2), 0); // отправка данных для дополнительного сервера

  int r = recv(fd, time, sizeof time, 0);
  if(r == -1){
    perror("recv");
  }
  
  printf("Time %d:%d:%d\n", time[0], time[1], time[2]);

  shmdt(memory);

  close(fd);
  return 0;
}
