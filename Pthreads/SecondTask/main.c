#include <stdio.h>
#include <pthread.h>

#define N 18

long a = 0;
pthread_mutex_t sync = PTHREAD_MUTEX_INITIALIZER;

void *thread_calc(){
  int i = 0;
  for(i = 0; i < 100000; i++){
    pthread_mutex_lock(&sync);
    a++;
    pthread_mutex_unlock(&sync);
  }
  printf("%ld\n", a);
  return NULL;
}

void main(){
  int i, j;
  int *s;
  pthread_t thread[N];

  for(i = 0; i < N; i++){
    pthread_create(&thread[i], NULL, thread_calc, NULL);
  }

  for(j = 0; j < N; j++){
    pthread_join(&thread[j],(void**)&s);
  }

   

  return 0;
}
