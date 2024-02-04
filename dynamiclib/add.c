#include <stdio.h>
int add(){
printf("Выбрано действие сложения\n");
int a,b,c = 0;
printf("Введите a\n");
scanf("%d", &a);
printf("Введите b\n");
scanf("%d", &b);
c = a + b;
return printf("Результат вычислений - %d", c);
}

