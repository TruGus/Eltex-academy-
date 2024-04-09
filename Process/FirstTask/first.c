#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t child_pid;
  int parent_pid;
  int status;


  child_pid = fork();

  if(child_pid == 0){
    printf("Child pid = %d\n", getpid());
    exit(status);
  }
  else{
    printf("Parent pid = %d\n", getpid());
    wait(&status);
    printf("status = %d\n", WEXITSTATUS(status));
  }


return 0;
}
