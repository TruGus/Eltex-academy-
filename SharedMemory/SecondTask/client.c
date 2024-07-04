#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include "function.h"
#include <sys/shm.h>

struct msgbuf{
  char All_message[20][20];
  char All_users[10][20];
  char Start_message[20];
  char Alert_message[20];
  char Your_name[20];
  char User_message[20];
  int usercount;
  int check_user;
  int check_message;
  short usercontrol;
  short messagecontrol;
  short allertcontrol;
};

int main(){

  struct msgbuf *memory;
  struct sembuf lock[2] = {{0,0,0},
  {0,1,0}};
  struct sembuf unlock[1] = {0,-1,0};

  char* path = "server";
 

  __key_t key = ftok(path, 1);
  __key_t key_for_sem = ftok(path, 2);
  int msg = shmget(key, 1, 0);
  int sem = semget(key_for_sem, 1, 0);

    if(key == -1){
    perror("key");
  }

    if(key_for_sem == -1){
    perror("key");
  }  

    if(msg < 0){
    perror("memory");
  } 

    if(sem < 0){
    perror("sem");
  } 

  memory = (struct msgbuf *) shmat(msg, 0, 0666);

  printf("%s\n", memory->Start_message);

  fgets(memory->Your_name, 20, stdin);
  strncpy(memory->All_users[memory->check_user], memory->Your_name, 20);
  memory->usercontrol = 1;
  memory->usercount++;
  semop(sem, &unlock,1);

  int i = 0;
  //получение всех старых сообщений
  while(i < memory->usercount){
    printf("%s", memory->All_users[i]);
    i++;
  }

  i = 0;
 
  while(i < memory->check_message){
    printf("%s\n", memory->All_message[i]);
    i++;
  }

  printf("Прием сообщений чата и пользователей завершен\n");
  printf("Выполняется вход....\n");

  sleep(2);

  graphic(memory->All_users[memory->check_user]);
  shmdt(memory);

return 0;
}

