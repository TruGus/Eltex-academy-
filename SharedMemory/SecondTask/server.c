#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include "function.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <mqueue.h>

#define N 2

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

  struct msgbuf *memory = {0};
  struct sembuf lock[2] = {{0,0,0},
  {0,1,0}};
  struct sembuf unlock[1] = {0,1,0};

  char* path = "server";
  char* start_message = "Your name:";
  char* alert_message = "New user";
  int usercount_buf = 0;
  int i = 0;
  
  __key_t key = ftok(path, 1);
  if(key == -1){
    perror("key");
  }
  __key_t key_for_sem = ftok(path, 2);
  if(key_for_sem == -1){
    perror("key");
  }  
  int msg = shmget(key, 1, IPC_CREAT | 0666);
  if(msg < 0){
    perror("memory");
  }  
  int sem = semget(key_for_sem, 1, IPC_CREAT | 0666);
  if(sem < 0){
    perror("sem");
  } 

  memory = (struct msgbuf *) shmat(msg, 0, 0666);
  memory->check_user = 0;
  memory->check_message = 0;
  memory->usercount = 0;

  //отправка стартовых сообщений клиенту
  strncpy(memory->Start_message, start_message, sizeof start_message + 1);
  strncpy(memory->Alert_message, alert_message, sizeof alert_message + 1);

  int stat_num = semctl(sem, 3, SETVAL, 0);
  int sem_num = semctl(sem, 3, GETVAL, 0);
  printf("Значение семафора на старте  %d\n", stat_num);

  

  /*shmdt(memory);
  shmctl(msg, IPC_RMID, 0);
  semctl(sem, 3, IPC_RMID);*/

  semop(sem, &lock,2);  
  while(memory->usercount < 10){
    //1
    //semop(sem, &lock,2);
    printf("Количество пользователей - %d\n", memory->usercount);
    printf("Usercontrol - %d\n", memory->usercontrol);
    sem_num = semctl(sem, 3, GETVAL, 0);
    printf("Значение семафора при ожидании клиента - %d\n", sem_num);

    if(memory->usercount == 1){
      //пересылка никнейма
      printf("Новый пользователь %d %s\n", memory->usercount, memory->All_users[memory->check_user]);
      //memory->usercount++;
      printf("Количество пользователей - %d\n", memory->usercount);
      memory->check_user++;
      memory->usercontrol = 0;
      //semop(sem, &lock,2);
    }
      
    //отправка уведомления клиенту
    if(memory->usercount > 1 && memory->usercontrol == 1){
      //semop(sem, &lock,2);
      printf("Новый пользователь %d %s\n", memory->usercount, memory->All_users[memory->check_user]);
      //memory->usercount++;
      memory->check_user++;
      memory->usercontrol = 0;
      memory->allertcontrol = 1;
      printf("%s\n", alert_message);
      //semop(sem, &lock,2);
    }

    //прием сообщений от клиентов
    sem_num = semctl(sem, 3, GETVAL, 0);
    printf("Значение семафора при ожидании клиента - %d\n", sem_num);
    //1
    semop(sem, &lock,2);
    
    memory->check_message++; 
    memcpy(memory->All_message[memory->check_message], memory->User_message, 20);
    
    strncpy(memory->All_message[memory->check_message], memory->User_message, 20);
    printf("Последнее принятое сообщение:\n");
    printf("%s\n", memory->User_message);

  }

  printf("Достигнут лимит пользователей\n");

  shmdt(memory);
  shmctl(msg, IPC_RMID, 0);
  semctl(sem, 3, IPC_RMID);

  return 0;    
}


  




 
   
    

    
   