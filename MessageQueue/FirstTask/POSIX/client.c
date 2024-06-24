#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>


int main(){
  
  char name[20] = "/my_queue";
  char buf[100] = "Hello";
  char recbuf[100] = "sd";
  int priority = 1;
  int rec_priority = 2;
 // fgets(name, 10, stdin);
  mqd_t msg = mq_open(name, O_RDWR);
   if(msg == -1){
    perror("msg");
  }

  ssize_t msgrcv = mq_receive(msg, recbuf,100, &priority);

  if(msgrcv == -1){
    perror("msg");
  }

  

  if(msgrcv != -1){
    printf("%s\n", recbuf);
  }
  
  mq_send(msg, buf, 100, rec_priority);
 // mq_send(msg, buf, 100, rec_priority);

  
  mq_close(msg);


return 0;
}
