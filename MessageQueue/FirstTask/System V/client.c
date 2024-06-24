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
 
 
  struct msgbuf sendbuf = {2, "Hello"};

   struct msgbuf recbuf;
 
  __key_t key = ftok("server", 1);
  int msg = msgget(key, 0);
  if(msg == 0){
    perror("msg");
    EXIT_FAILURE;
  }

  msgrcv(msg,  &recbuf, 10, 3, 0);
  msgsnd(msg, &sendbuf, 10, 0);

  
  
  printf("%s\n", recbuf.buf);


return 0;
}

