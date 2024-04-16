#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "function.h"

#define N 3 //количество людей
//#define M 5 //количество магазинов
#define G 1 //количество погрузчиков

pthread_mutex_t sync = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//long FirstSupemarket = 50000;
//long SecondSupemarket = 50000;
int k = 1;

void main(){
  int i, j;
  int *s;
  int Supemarkets[M];
  for(i = 0; i<M; i++){
    Supemarkets[i] = 8000 + rand() % 10000;
    printf("%d\n", Supemarkets[i]);
  }
  pthread_t thread_person[N + G];
  pthread_t thread_truck[G];

  for(i = 0; i < N + G; i++){
    if(i == N){
      pthread_create(&thread_person[i], NULL, restore_supemarket, &Supemarkets);
      break;
    }
     pthread_create(&thread_person[i], NULL, walk_to_supemarket, &Supemarkets);
  }

  for(j = 0; j < N; j++){
    pthread_join(&thread_person[j],(void**)&s);
  }

  k = -1;
  pthread_join(&thread_truck[0],(void**)&s);

  return 0;
}

void *walk_to_supemarket(int Supemarkets[M]){
  int Need = 80000 + rand() % 100000;
  while(Need > 0){
    for(int i = 0; i < M; i++){
      pthread_mutex_lock(&sync);
      if(Supemarkets[i] > 0){
        printf("id - %ld\nCодержимое маркета - %d\nТекущая потребность - %d\n",pthread_self(), Supemarkets[i], Need);
        if(Supemarkets[i] > Need){
          Supemarkets[i] = Supemarkets[i] - Need;
          Need = 0;
          printf("id - %ld\nПотребность удовлетворена----------------------\n",pthread_self());
          pthread_mutex_unlock(&sync);
          break;
        }
        Need = Need - Supemarkets[i];
        Supemarkets[i] = 0;
        printf("Новая потребность - %d\nОстаток в магазине %d - %d\n*******\n", Need, i, Supemarkets[i]);
        pthread_mutex_unlock(&sync);
        sleep(2);
      }
      else{
        pthread_mutex_unlock(&sync);
        pthread_cond_signal(&cond);
      }
    }
  }
  return NULL;
}

void *restore_supemarket(int Supemarkets[M]){
  int i = 0;

  while(k == 1){
  pthread_mutex_lock(&sync);
  pthread_cond_wait(&cond, &sync);
    while(i < 5){
    Supemarkets[i] = 15000;
    i++;
    printf("Магазин пополнен на 8000\n######\n");
    }
    i = 0;
    pthread_mutex_unlock(&sync);
  }

  
  return NULL;
}


