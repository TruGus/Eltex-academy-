#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>


int main(){
  struct mq_attr{
    long mq_flags;
    long mq_maxmsg;
    long mq_msgsize;
    long mq_curmsgs;
  };

  struct mq_attr attr;
  attr.mq_maxmsg = 3;
  attr.mq_msgsize = 100;
  attr.mq_curmsgs = 0;
  
  char name[20] = "/my_queue";
  char buf[10] = "Hi";
  char recbuf[100];
  int priority = 1;
  int rec_priority = 2;
 // fgets(name, 10, stdin);
  mqd_t msg = mq_open(name, O_CREAT | O_RDWR, 0666, &attr);
  if(msg == -1){
    perror("msg");
  }

  int send = mq_send(msg, buf, attr.mq_msgsize, priority);
  if(send < 0){
    perror("send");
  }

  send = mq_send(msg, buf, attr.mq_msgsize, priority);
  if(send < 0){
    perror("send");
  }

   sleep(3);
  size_t msgrcv = mq_receive(msg, recbuf, 100, &priority);
  if(msgrcv == -1){
    perror("msg");
  }

  printf("%s\n", recbuf);
  
  mq_close(msg);

  mq_unlink(name);

return 0;
}
