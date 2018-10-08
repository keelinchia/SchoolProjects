#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

int numbers[20];
void* write_odd();
void* write_even();
pthread_mutex_t mutex;

int main(int argc, char* argv[])
{
  int i;
  pthread_t workers[NUM_THREADS];
  pthread_attr_t attr;

  pthread_attr_init(&attr); /* Get the default attributes */
  pthread_mutex_init(&mutex, NULL); /* Create mutex lock */

  /* Create the threads for each operation */
  pthread_create(&workers[0], &attr, write_odd, NULL);
  pthread_create(&workers[1], &attr, write_even, NULL);

  /* Wait for all threads to terminate */
  pthread_join(workers[0], NULL);
  pthread_join(workers[1], NULL);
  
  /* Output the results */
  for (i = 0; i < 20; i++) {
    printf("%5d", numbers[i]);
  }
  printf("\n");

  return 0; 
}

/* Function Implmentations */
void* write_odd(){

  int i;
  
  for (i = 0; i < 20; i += 2) {
    pthread_mutex_lock(&mutex);
    numbers[i] = i+1;
    pthread_mutex_unlock(&mutex);
  }
  
  pthread_exit(0);
}

void* write_even(){

  int i;
  
  for (i = 1; i < 20; i += 2) {
    pthread_mutex_lock(&mutex);
    numbers[i] = i+1;
    pthread_mutex_unlock(&mutex);
  }
  
  pthread_exit(0);
}




