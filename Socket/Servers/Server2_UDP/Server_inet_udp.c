#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "function.h"
#include <time.h>

uint16_t port_number = 7777; //порт основного сервера

int main(){

  int *s;

  //создание разделяемой памяти для общения серверов

  char* path = "bin";
  int unlock_port; //новый порт для подключения
  struct msgbuf *memory;
  
  __key_t key = ftok(path, 1);
  __key_t key_for_sem = ftok(path, 2);
  int msg = shmget(key, 1, 01000 | 0666);
  int sem = semget(key_for_sem, 1, 01000 | 0666);
   if(msg == 0){
    perror("msg");
  }

  memory = (struct msgbuf *) shmat(msg, 0, 0666);
  for(int i = 0; i<SERV_NUMBER; i++){
    memory->server_lock[i] = 0;
  }

  //создание слушающего сервера
  struct sockaddr_in adr;
  struct sockaddr_in adrclient;
  pthread_t add_serv[SERV_NUMBER];
  int size, size_cl;
  char recbuf[64];
  
  size_cl = sizeof(adrclient);
  size = sizeof(adr);

  int main_servfd = socket(AF_INET, SOCK_DGRAM, 0);
  adr.sin_family = AF_INET;
  adr.sin_port = htons(port_number);
  socklen_t socklen = sizeof(adr);
  
  bind(main_servfd, (struct sockaddr *)&adr, socklen);
  int i = 0;// переменная цикла
  
  //создание пула серверов
    while(i < SERV_NUMBER){ 
      pthread_create(&add_serv[i], NULL, dop_serv, &i);
      sleep(1);
      i++;
    }
  
  port_number++;

  //поиск свободного сервера
  while(1){
      recvfrom(main_servfd,recbuf,size,0,(struct sockaddr *) &adrclient,&size_cl);
      printf("%s\n", recbuf);
    for(int k = 0; k < SERV_NUMBER; k++){
      if(memory->server_lock[k] == 0){
        unlock_port = port_number + k;
        //передача свободного порта клиенту
        sendto(main_servfd, &unlock_port ,size,0,(struct sockaddr *) &adrclient, size_cl);//реакция клиента
        sendto(main_servfd, &k ,size,0,(struct sockaddr *) &adrclient, size_cl);//реакция клиента
        unlock_port = port_number;
        break;
      }
      else{
        sleep(1);
        memory->all_server_lock = 1;
      }  
    }
  }

  for(int j = 0; j < SERV_NUMBER; j++){
    pthread_join(&add_serv[j],(void**)&s);
  }
  
  close(main_servfd);
  shmdt(memory);
  shmctl(msg, IPC_RMID, 0);
  semctl(sem, 3, IPC_RMID);

  return 0;
}

void* dop_serv(int *i){
  int serv_num = *i;
  printf("Эта переменная равна %d\n", serv_num);
 
  int our_port = 7777 + serv_num;
  printf("Запущен сервер № %d, порт - %d\n", serv_num, our_port);

  //подключение к разделяемой памяти
  char* path = "bin";
  struct msgbuf *memory;
  __key_t key = ftok(path, 1);
  __key_t key_for_sem = ftok(path, 2);
  int msg = shmget(key, 1, 0);
  int sem = semget(key_for_sem, 1, 0);
   if(msg == 0){
    perror("msg");
  }

  struct sockaddr_in adr;
  struct sockaddr_in adrclient;
  char recbuf[64];
  int size, size_cl;

  int main_servfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(main_servfd == -1){
    perror("socket");
  }
  adr.sin_family = AF_INET;
  adr.sin_port = htons(our_port);
  socklen_t socklen = sizeof(adr);
    size_cl = sizeof(adrclient);
  size = sizeof(adr);
  bind(main_servfd, (struct sockaddr *)&adr, socklen);
  
  memory = (struct msgbuf *) shmat(msg, 0, 0666);
  memory->server_lock[*i] = 0; //0 - свободный сервер

   int test[3]; 
   time_t mytime;
   struct tm *now;
  
  while(1){
    printf("Статус сервера - %d свободен\n", *i);
    
    recvfrom(main_servfd,recbuf,size,0,(struct sockaddr *) &adrclient,&size_cl);
    printf("%s\n", recbuf);// подключение успешно
    printf("Клиент подключен\n");
    memory->server_lock[*i] = 1;//блокировка сервера
    printf("Статус сервера %d - занят\n", *i);
    
   
    time(&mytime);
    now = localtime(&mytime);
    test[0] = now->tm_hour;
    test[1] = now->tm_min;
    test[2] = now->tm_sec;

    printf("Time %d:%d:%d\n", test[0], test[1], test[2]);
    int s = sendto(main_servfd,test,size,0,(struct sockaddr *) &adrclient, size_cl);
    if(s == -1){
      perror("send");
    }
    memory->server_lock[serv_num] = 0;//разблокировка сервера
  }

  shmdt(memory);
}