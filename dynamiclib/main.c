#include <stdio.h>
#include "libdcalc.h"
int main(void){
int choose = 0;
while(choose != 5){
printf("Выберите действие\n 1 - сложение \n2 - вычитание \n3 - умножение \n4 - деление\n 5 - Выход\n");
scanf("%d",&choose);
switch(choose){

case 1:
add();
break;

case 2:
sub();
break;

case 3:
mul();
break;

case 4:
div();
break;

case 5:
break;

default:
printf("Выбрано неверное действие");
}

}
return 0;
}

