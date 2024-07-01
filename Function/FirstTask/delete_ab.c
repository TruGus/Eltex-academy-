#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include <string.h>


void* delete_ab(struct list* people, int* number_of_abonent, int* lenght){

 int search_num_s = 0;
 int buf = 0;
 printf("Введите номер абонента, которого хотите удалить, список начинается с нуля: ");
 search_num_s = getchar();
 buf = getchar();
 search_num_s = search_num_s - 48;

 printf("Имя:");
 puts((people + search_num_s)->name);
 printf("Фамилия:");
 puts((people + search_num_s)->second_name);
 printf("Телефон:");
 puts((people + search_num_s)->tel);


 for (int i = search_num_s; i < (*number_of_abonent); i++){
   strcpy((people + i)->name, (people + i + 1)->name);
   strcpy((people + i)->second_name, (people + i + 1)->second_name);
   strcpy((people + i)->tel, (people + i + 1)->tel);
 }

  return people;
}
