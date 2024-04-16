#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>


int main(){
  FILE* client;
  char word[10] = "Hi";
  char *myfifo = "/tmp/myfifo";
  mkfifo(myfifo, 0200);
  client = open(myfifo,O_WRONLY);

  write(client,"Hi", sizeof("Hi"));
  close(client);
  


return 0;
}
