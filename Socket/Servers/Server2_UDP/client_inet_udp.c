#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "function.h"

int main(){
  //прописать ожидание сервера
  char* path = "bin";
  struct msgbuf *memory;
  __key_t key = ftok(path, 1);
  __key_t key_for_sem = ftok(path, 2);
  int msg = shmget(key, 1, 0);
  int sem = semget(key_for_sem, 1, 0);

  memory = (struct msgbuf *) shmat(msg, 0, 0666);

  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  char sendbuf[64] = "Client";
  char sendbuf_2[64] = "Попытка подключения клиента";
  char recbuf[64];
  int port_number = 0;
  int serv_number = 0;
  int time[3];
  struct sockaddr_in adr = {0};
  adr.sin_family = AF_INET;
  adr.sin_port = htons(7777);
  int size = sizeof(adr);
  int con = connect(fd, (struct sockaddr *) &adr, size);
  if(con == -1){
    perror("con");
  }

  
  printf("Прием нового порта и номера сервера\n");
  int s = send(fd,sendbuf_2,sizeof(sendbuf_2), 0);
  if(memory->all_server_lock == 1){
     sleep(1);
     s = send(fd,sendbuf_2,sizeof(sendbuf_2), 0);
  }
  recv(fd, &port_number, sizeof port_number,0);
  recv(fd, &serv_number, sizeof serv_number,0);
  printf("Номер сервера - %d\n", serv_number);
  printf("Новый порт для подключения - %d\n", port_number);

  adr.sin_family = AF_INET;
  adr.sin_port = htons(port_number);
  size = sizeof(adr);
  con = connect(fd, (struct sockaddr *) &adr, size);
  if(con == -1){
    perror("con");
  }
  else{
    printf("Подключение выполнено\n");
  }

   s = send(fd,sendbuf,sizeof(sendbuf), 0);
   if(s == -1){
    perror("send");
  }

  int r = recv(fd, time, sizeof time, 0);
  if(r == -1){
    perror("recv");
  }
  

  printf("Time %d:%d:%d\n", time[0], time[1], time[2]);

  shmdt(memory);

  close(fd);
  return 0;
}
