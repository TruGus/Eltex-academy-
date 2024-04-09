#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define LEN 100

int main(){
    pid_t child_pid;
    int status;
    int whileStatus = 1;
    char ex;
    char name[LEN];
    char keys[LEN];
    char commandDefault[LEN] = "/bin/";
    char command[LEN] = "/bin/";

    while(whileStatus > 0){

    strcpy(command, commandDefault);
    printf("Имя команды:");
    fgets(name, 20, stdin);
    if(name == "exit\n"){
      printf("ddddd\n");
      break;
      whileStatus--;
    }
    strcat(command, name);
    printf("Итоговый путь - %s\n",command);

    printf("Опции программы:");
    fgets(keys, 20, stdin);

    for(int i = 0; i <= LEN; i++){
      if(name[i] == '\n')
        name[i] = '\0';
      if(command[i] == '\n')
        command[i] = '\0';
      if(keys[i] == '\n')
        keys[i] = '\0';
    }

    child_pid = fork();
    if(child_pid == 0){
      execl(command, name, keys, NULL);
      exit(5);
    }
    else{
      printf("Выход - q\n");
      ex = getchar();
      if(ex == 'q')
        exit(status);
      wait(&status);
    }
}
  return 0;
}
