#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t child_pid;
  pid_t child_pid_left_branch;
  pid_t under_child_pid;
  pid_t under_child_pid_left_branch_one;
  pid_t under_child_pid_left_branch_two;
  int parent_pid;
  int status;


  child_pid = fork();

  if(child_pid == 0){
    printf("Child pid = %d\n", getpid());
    printf("----------\n");
    under_child_pid = fork();
    if(under_child_pid == 0){
      printf("under Child pid = %d\n", getpid());
    }
    else{
      printf("Parent pid = %d\n", getpid());
      wait(&status);
    }
  }

 else{
   printf("Parent pid = %d\n", getpid());
   wait(&status);
   printf("Parent pid = %d\n", getpid());
   child_pid_left_branch = fork();

   if(child_pid_left_branch == 0){
     printf("Child pid in left branch = %d\n", getpid());
     under_child_pid_left_branch_one = fork();
     under_child_pid_left_branch_two = fork();
     if(under_child_pid_left_branch_one == 0 && under_child_pid_left_branch_two != 0){
       printf("under Child pid in left branch one = %d\n", getpid());
     }

     else if(under_child_pid_left_branch_two == 0 && under_child_pid_left_branch_one != 0){
       printf("under Child pid in left branch two = %d\n", getpid());
     }

     else if(under_child_pid_left_branch_one == 0 && under_child_pid_left_branch_two != 0){
       printf("Parent pid = %d\n", getpid());
       wait(&status);
     }
   }
 }

return 0;
}
