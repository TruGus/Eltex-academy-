#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include "function.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <mqueue.h>

#define N 2

struct msgbuf{
  long mtype;
  char buf[20];
  int size;
};

struct msgbuf start_message = {5, "Your name:"};
struct msgbuf username;
struct msgbuf usersmsg = {0};

int main(){

  int userscount = 0;
  int usercount_buf = 0;
  int i = 0;
  struct msgbuf alert_message = {2, "New user"};
  struct msgbuf new_message = {2, "New message"};
 
  key_t key_for_servmsg = ftok("server", 1);
  key_t key_for_servmsg2 = ftok("server", 2);
  key_t key_for_clientmsg = ftok("server", 3);
  key_t key_for_old_msg = ftok("server", 4);
  int msg_serv = msgget(key_for_servmsg, IPC_CREAT | 0666);
  int msg_serv_two = msgget(key_for_servmsg2, IPC_CREAT | 0666);
  int msg_serv_third = msgget(key_for_clientmsg, IPC_CREAT | 0666);
  int old_msg_que = msgget(key_for_old_msg, IPC_CREAT | 0666);

  if (key_for_servmsg == -1){
    perror("key");
  }
  if (msg_serv < 0){
    perror("msg");
  }   
    
  while(userscount < 10){
    //отправка стартовых сообщений клиенту
    int send = msgsnd(msg_serv, &start_message, 25, IPC_NOWAIT);
    if(send < 0){
      perror("send");
    }

    size_t rcvmsg = msgrcv(msg_serv, &username, 60, 4, IPC_NOWAIT);
    if(rcvmsg == -1){
      perror("rcv");
    }
    else{
      userscount++;
    }
        
    if(userscount == 0){
      int send = msgsnd(msg_serv, &start_message, 60, 0);
      if(send < 0){
        perror("send");
      }

      size_t rcvmsg = msgrcv(msg_serv, &username, 60, 4, 0);
      if(rcvmsg == -1){
        perror("rcv");
      }
      //пересылка никнейма
      username.mtype = 7;
      username.size = strlen(username.buf) + 1 + 4;
      send = msgsnd(msg_serv, &username, 60, 0);
      if(send < 0){
        perror("send");
      }

      printf("Новый пользователь %d %s\n", userscount, username.buf);
      userscount++;
      usercount_buf = userscount;
    }
      
    //отправка уведомления клиенту
    if(userscount > 1 && userscount != usercount_buf){
      printf("Новый пользователь %d %s\n", userscount, username.buf);
      username.size = strlen(username.buf) + 1 + 4;
      //отправка никнейма нового 
      username.mtype = 7;
      for(int i = 0; i < userscount; i++){
        int send = msgsnd(msg_serv, &username, 60, 0);
        if(send < 0){
          perror("send");
        }
      }

      printf("%d\n", userscount);
      usercount_buf = userscount;
      //отправка самого уведомления
      send = msgsnd(msg_serv_two, &alert_message, sizeof(alert_message), 0);
      if(send < 0){
        perror("send");
      }
    }


    //прием сообщений от клиентов
    memset(usersmsg.buf, '0', 20);
    rcvmsg = msgrcv(msg_serv_third, &usersmsg, 60, 3, 0);//прием сообщений от клиента
    if(rcvmsg == -1){
        perror("rcv");
    }
    printf("прием сообщений\n");

    printf("%s\n", usersmsg.buf);
    usersmsg.size = sizeof(struct msgbuf) - 8 - 4;
    printf("%d\n", usersmsg.size);
    usersmsg.mtype = 5;
      
    //отправка сообщений клиентам
    for(int i = 0; i < userscount; i++){
      send = msgsnd(msg_serv_two, &usersmsg, usersmsg.size, 0);
      if(send < 0){
        perror("send");
      }
      printf("%s\n", usersmsg.buf);
      //отправка сообщений в общий буфер
      send = msgsnd(old_msg_que, &usersmsg, usersmsg.size, IPC_NOWAIT);
      if(send < 0){
        perror("send");
      }
    }


  }

  printf("Достигнут лимит пользователей\n");

  msgctl(msg_serv, IPC_RMID, 0);
  msgctl(msg_serv_two, IPC_RMID, 0);
  msgctl(msg_serv_third, IPC_RMID, 0);
  msgctl(old_msg_que, IPC_RMID, 0);


  return 0;
}

 
   
    

    
   