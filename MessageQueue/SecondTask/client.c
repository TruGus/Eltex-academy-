#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "function.h"


int main(){
 
  struct msgbuf{
    long mtype;
    char buf[20];
  };
  struct msgbuf user_name;
  struct msgbuf serv_msg;
  struct msgbuf all_msg = {0};
  struct msqid_ds qstatus = {0};

  key_t key_for_servmsg = ftok("server", 1);
  int msg_serv = msgget(key_for_servmsg, 0);

  key_t key_for_old_msg = ftok("server", 4);
  int old_msg_que = msgget(key_for_old_msg, 0);
    
  if(key_for_servmsg == -1){
      perror("key");
  }

  if(msg_serv > 0){
      perror("msg");
  }


  size_t rcvmsg = msgrcv(msg_serv, &serv_msg, 60, 5, 0);
  if(rcvmsg == -1){
    perror("rcv");
  }

  printf("%s\n", serv_msg.buf);

  fgets(user_name.buf, 20, stdin);

  user_name.mtype = 4;

  int send = msgsnd(msg_serv, &user_name, 60, 0);
  if(send < 0){
    perror("send");
  }

  msgqnum_t num_of_msg = 0;
  //получение всех сообщений чата
  if(msgctl(old_msg_que, IPC_STAT, &qstatus)< 0){
    perror("ctl");
  }

  while(qstatus.msg_qnum > num_of_msg){
    msgrcv(old_msg_que, &all_msg, 60, 0, IPC_NOWAIT);
    printf("%s\n", all_msg.buf);
    printf("%ld\n", qstatus.msg_qnum);
    msgctl(old_msg_que, IPC_STAT, &qstatus);
  }

  printf("Прием сообщений чата завершен\n");
  printf("Выполняется вход....\n");

  sleep(2);

  graphic(user_name.buf);

return 0;
}

