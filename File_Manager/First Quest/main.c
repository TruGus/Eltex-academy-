#include <stdio.h>

char line[] = "String from file";

int main(){

  int count  = 20;
  FILE *fd  = fopen("output.txt", "w+");
  if(fd == -1){
    printf("Error");
  }
  fputs(line, fd);
  fseek(fd, 0L, SEEK_END);
  fgets(line, count, fd);
  printf("%s\n", line);

  close(fd);

return 0;
}
