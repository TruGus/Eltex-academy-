#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
  struct msgbuf{
    long mtype;
    char buf[10];
  };
  char* path = "bin";
 
  struct msgbuf sendbuf = {3, "Hi"};
  struct msgbuf recbuf;


  __key_t key = ftok("server", 1);
  int msg = msgget(key, IPC_CREAT | 0666);
  
  if(msg == 0){
    perror("msg");
    EXIT_FAILURE;
  }

  msgsnd(msg, &sendbuf, 10, 0);

  size_t rcvmsg = msgrcv(msg, &recbuf, 10, 2, 0);
  if(rcvmsg == -1){
    perror("rcv");
  }

  printf("%s\n", recbuf.buf);

  msgctl(msg, IPC_RMID, 0);

return 0;
}
