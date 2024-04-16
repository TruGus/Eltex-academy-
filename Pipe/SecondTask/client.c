#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
  FILE* client;
  char word[10];
  char *myfifo = "/tmp/myfifo";
  if((client = open(myfifo,O_RDONLY)) != 0){
    perror("Ошибка открытия канала");
  }
  
  read(client, word, 10);
  printf("%s\n", word);
  close(client);

return 0;
}
