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

  char* message = "Hi";
  struct msgbuf* memory; 

    struct sembuf lock[2] = {{0,0,0},
  {0,1,0}};
  struct sembuf unlock[1] = {0,1,0};
  

 // fgets(path, 20 ,stdin);
  sem_t* sem = sem_open(SEMAPHORE_NAME, O_CREAT | O_RDWR, 0666);

  int sharedmem_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
  if(sharedmem_fd == -1){
    perror("open");
  }

  if(sem == SEM_FAILED){
    perror("sem");
  }

  ftruncate(sharedmem_fd, sizeof (struct msgbuf) + 1);
  memory = (struct msgbuf*) mmap(NULL, sizeof (struct msgbuf) + 1, PROT_WRITE | PROT_READ, MAP_SHARED, sharedmem_fd, 0);
  if(memory == -1){
    perror("mmap");
    return 1;
  }
   sem_post(sem);
   perror("sem post");
   strcpy(memory->server_message, message);

   //strcpy(memory->server_message, message);
   sem_wait(sem);
   sem_wait(sem);
   //sem_wait(sem);
  // sem_wait(sem);

   printf("%s\n", memory->server_message);

   munmap(memory, 100);
   shm_unlink(SHARED_MEMORY_NAME);
   sem_close(sem);
   sem_unlink(SEMAPHORE_NAME);

return 0;
}
