#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

int main(){
  struct msgbuf{
    char server_message[10];
  };
  char* path = "bin";
  char* message = "Hi"; 
  
  struct msgbuf *memory;
  struct sembuf lock[2] = {{0,0,0},
  {0,1,0}};
  struct sembuf unlock[1] = {0,-1,0};
  

  __key_t key = ftok(path, 1);
  __key_t key_for_sem = ftok(path, 2);
  int msg = shmget(key, 1, 01000 | 0666);
  int sem = semget(key_for_sem, 1, 01000 | 0666);
  
   if(msg == 0){
    perror("msg");
    EXIT_FAILURE;
  }

   memory = (struct msgbuf *) shmat(msg, 0, 0666);
   semop(sem, &lock,2);
   strcpy(memory->server_message, message);
   semop(sem, &lock,2);

   printf("%s\n", memory->server_message);

   shmdt(memory);
   shmctl(msg, IPC_RMID, 0);
   semctl(sem, 3, IPC_RMID);

return 0;
}
