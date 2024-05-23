#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "function.h"
#include <time.h>

uint16_t port_number = 7777; // порт основного сервера

int main(){
  //создание слушающего сокета
  struct client_data* client_list;
  int *s;
  int offset_client = 0;
  pthread_t *add_serv = NULL;
  add_serv = (pthread_t*) malloc(sizeof (unsigned long));
  int i = 1; // подсчет клиентов
  struct sockaddr_in serv, client = {0};

  int main_serv_fd = socket(AF_INET, SOCK_STREAM, 0);
  serv.sin_family = AF_INET;
  serv.sin_port = htons(port_number);
  socklen_t adrlen = sizeof (serv);
  int clientfd;
  bind(main_serv_fd, (struct sockaddr *)&serv, sizeof(serv));
  listen(main_serv_fd, 5);

  // прием клиентов и создание нового потока
  while(i < 10){
      clientfd = accept(main_serv_fd, (struct sockaddr *) &client, &adrlen);
      printf("Подключился новый клиент его номер - %d\n", i);
      add_serv = (pthread_t*) realloc(add_serv, (sizeof (unsigned long)) * i);
      pthread_create((add_serv + i), NULL, dop_serv, &clientfd);
      i++;
  }


  for(int j = 0; j < 5; j++){
    pthread_join(&add_serv[j],(void**)&s);
  }
  
  close(main_serv_fd);
  free(add_serv);
  return 0;
}

//функция для параллельного сервера
void *dop_serv(int* clientfd){
  
  char recbuf[64];

  int test[3]; //сюда записываем время
  time_t mytime;
  time(&mytime);

  struct tm *now = localtime(&mytime);
  test[0] = now->tm_hour;
  test[1] = now->tm_min;
  test[2] = now->tm_sec;
  recv(*clientfd, recbuf, sizeof recbuf, 0);
 
  printf("%s\n", recbuf);

 
  send(*clientfd, test, sizeof (test), 0);
  printf("Текущее время отправлено\n");

  close(*clientfd);
}
