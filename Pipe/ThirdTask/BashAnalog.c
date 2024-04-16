#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define LEN 100

int main(){
    pid_t child_pid, child_pid_two;
    int status;
    int whileStatus = 1;
    int channels[2];
    char ex;
    char name[LEN];
    char nameTwo[LEN];
    char keys[LEN];
    char keysTwo[LEN];
    char commandDefault[LEN] = "/bin/";
    char command[LEN] = "/bin/";
    char commandTwo[LEN] = "/bin/";

    if(pipe(channels)){
    perror("ошибка при создании канала");
    exit(1);
    }

    while(whileStatus > 0){

    strcpy(command, commandDefault);
    printf("Имя команды 1:");
    fgets(name, 20, stdin);
    if(name == "exit\n"){
      break;
      whileStatus--;
    }
    strcat(command, name);
    printf("Итоговый путь - %s\n",command);

    printf("Опции программы 1:");
    fgets(keys, 20, stdin);

    for(int i = 0; i <= LEN; i++){
      if(name[i] == '\n')
        name[i] = '\0';
      if(command[i] == '\n')
        command[i] = '\0';
      if(keys[i] == '\n')
        keys[i] = '\0';
    }

    strcpy(commandTwo,commandDefault);
    printf("Имя команды 2:");
    fgets(nameTwo, 20, stdin);
    strcat(commandTwo, nameTwo);
    printf("Итоговый путь - %s\n",commandTwo);
    printf("Опции программы 2:");
    fgets(keysTwo, 20, stdin);

    for(int i = 0; i <= LEN; i++){
      if(nameTwo[i] == '\n')
        nameTwo[i] = '\0';
      if(commandTwo[i] == '\n')
        commandTwo[i] = '\0';
      if(keysTwo[i] == '\n')
        keysTwo[i] = '\0';
    }

    child_pid = fork();
    if(child_pid == 0){
      close(channels[0]);
      dup2(channels[1], 1);
      execl(command, name, keys, NULL);
      exit(status);
    }
    else{
      wait(&status);
      child_pid_two = fork();
      if(child_pid_two == 0){
          close(channels[1]);
          dup2(channels[0], 0);
          execl(commandTwo, nameTwo, keysTwo, NULL);
          exit(status);
      }
      else{
        printf("Результат - %s %s | %s %s\n", name,keys,nameTwo,keysTwo);
        printf("Выход - q\n");
        ex = getchar();
        if(ex == 'q')
          exit(status);
        wait(&status);
      }
    }
}
  return 0;
}
