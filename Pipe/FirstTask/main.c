#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  int channels[2];
  int status;
  char word[10] = "Hi";
  char buf[10];
  pid_t pid;
  
  if(pipe(channels)){
    perror("ошибка при создании канала");
    exit(1);
  }

  write(channels[1], word, 10);

  if((pid = fork()) == 0){
      
    close(channels[1]);
    read(channels[0], buf, sizeof(buf));
    printf("%s\n", buf);
    exit(0);
  }
  else{
    close(channels[0]);
    wait(&status);
  }

return 0;
}
