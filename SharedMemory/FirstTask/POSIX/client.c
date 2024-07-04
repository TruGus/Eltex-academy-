#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define SHARED_MEMORY_NAME "/my"
#define SEMAPHORE_NAME "/bin"

int main(){
  struct msgbuf{
    char server_message[10];
  };
 
  char* message = "Hello";
  struct msgbuf* memory; 
  
  
  sem_t *sem = sem_open(SEMAPHORE_NAME, 0);
  int sharedmem_fd = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0666);
    if(sharedmem_fd == -1){
    perror("open");
  }

    if(sem == SEM_FAILED){
    perror("sem");
  }
  

  ftruncate(sharedmem_fd, 1);
  memory = (struct msgbuf*) mmap(NULL, sizeof (struct msgbuf) + 1, PROT_WRITE | PROT_READ, MAP_SHARED,  sharedmem_fd, 0);
      if(memory == -1){
    perror("mmap");
    return 1;
  }
  sem_post(sem);
  printf("%s\n", memory->server_message);
  strcpy(memory->server_message, message);
  //sem_wait(sem);
  

   

   munmap(memory, 1);
   sem_close(sem);

return 0;
}
