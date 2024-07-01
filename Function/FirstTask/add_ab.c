#include <stdio.h>
#include "function.h"
#include <stdlib.h>
#include <string.h>


void* add_ab(struct list* people, int* number_of_abonent, int* lenght){

  if(*number_of_abonent == 0){
    people = (struct list*)calloc(1,sizeof(struct list));
    if(people == NULL){
      printf("Ошибка выделения памяти");
    }
  }

  else{
    people = (struct list*)realloc(people, sizeof(struct list) * (*number_of_abonent+1));
    if(people == NULL){
      printf("Ошибка выделения памяти");
    }
  }

  printf("Введите имя нового абонента: ");
  fgets((people + *number_of_abonent)->name, 20, stdin);
  (people + *number_of_abonent)->name[strcspn((people + *number_of_abonent)->name, "\n")] = '\0';
  puts((people + *number_of_abonent)->name);

  printf("Введите фамилию нового абонента: ");
  fgets((people + *number_of_abonent)->second_name, 20, stdin);
  (people + *number_of_abonent)->second_name[strcspn((people + *number_of_abonent)->second_name, "\n")] = '\0';
  puts((people + *number_of_abonent)->second_name);


  printf("Введите номер нового абонента: ");
  fgets((people + *number_of_abonent)->tel, 20, stdin);
  (people + *number_of_abonent)->tel[strcspn((people + *number_of_abonent)->tel, "\n")] = '\0';
  puts((people + *number_of_abonent)->tel);


  return people;
}
