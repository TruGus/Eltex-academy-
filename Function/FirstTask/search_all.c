#include <stdio.h>
#include <stdlib.h>
#include "function.h"


void* show_all(struct list* people, int* lenght){

  int a = *lenght;
  for(int i = 0; i < a; i++){
    printf("Имя: ");
    puts((people + i)->name);
    printf("Фамилия: ");
    puts((people + i)->second_name);
    printf("Телефон: ");
    puts((people + i)->tel);

  }




}
