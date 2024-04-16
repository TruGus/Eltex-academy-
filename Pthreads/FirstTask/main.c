#include <stdio.h>
#include <pthread.h>

#define N 5

void *thread_calc(void *args){
  int *i = (int*)args;
  printf("thread num %d\n", *i);
  return NULL;
}

void main(){
  int i, j;
  int *s;
  int new_arr[N];
  pthread_t thread[N];

  for(i = 0; i < N; i++){
    new_arr[i] = i;
    pthread_create(&thread[i], NULL, thread_calc, (void *)&new_arr[i]);
  }

  for(j = 0; j < N; j++){
    pthread_join(&thread[j],(void**)&s);
  }

  return 0;
}
