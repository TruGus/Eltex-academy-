#include <stdio.h>
#include "function.h"
#include <malloc.h>

int lenght = 0;
int number_of_abonent = 0;// счетчик уже имеющихся абонентов
int *ptr_number_of_abonent = &number_of_abonent;
int *ptr_lenght = &lenght;


int main(){

int choose = 0;
int buf = 0; // переменная для очистки буфера
struct list *people;


while(choose != '5'){

  puts("Выберите опцию 1 - добавить абонента  2 - удалить абонента  3 - поиск абонента  4 - Вывести список 5 - Выход");

  choose = getchar();
  buf = getchar();
  if(choose != '\n' && choose != EOF){
   switch(choose){

     case '1':
     lenght++;
     people = add_ab(people, ptr_number_of_abonent, ptr_lenght);
     number_of_abonent++;
     break;

     case '2':
     people = delete_ab(people, ptr_number_of_abonent, ptr_lenght);
     lenght--;
     number_of_abonent--;
     people = realloc(people, sizeof(struct list) * lenght);
     if(people == NULL){
       printf("Ошибка выделения памяти");
     }
     break;

     case '3':
     search_ab(people);
     break;

     case '4':
     show_all(people, ptr_lenght);
     break;

     case '5':
     break;

     default:
     printf("Выбрана неверная опция");
     break;
   }
 }
 }
free(people);

  return 0;
}
