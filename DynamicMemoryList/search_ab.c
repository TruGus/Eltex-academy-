#include <stdio.h>
#include <stdlib.h>
#include "function.h"




void* search_ab(struct list* people){

int search_num_s = 0;
int buf = 0;
printf("Введите номер абонента, которого хотите найти. Список начинается с нуля: ");

 search_num_s = getchar();
 buf = getchar();
printf("%d", (search_num_s - 48));
search_num_s = search_num_s - 48;
 printf("Имя:");
 puts((people + search_num_s)->name);
 printf("Фамилия:");
 puts((people + search_num_s)->second_name);
 printf("Телефон:");
 puts((people + search_num_s)->tel);

}
