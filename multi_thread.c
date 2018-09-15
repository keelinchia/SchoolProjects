#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3

int avg, max, min;
void* do_avg(void* param);
void* do_max(void* param);
void* do_min(void* param);

int main(int argc, char* argv[])
{
  pthread_t workers[NUM_THREADS];
  pthread_attr_t attr;

  if (argc < 2) {
    fprintf(stderr, "usage: a.out <interger values>\n");
    return -1; 
  }

  pthread_attr_init(&attr); /* Get the default attributes */
  /* Create the threads for each operation */
  pthread_create(&workers[0], &attr, do_avg, argv);
  pthread_create(&workers[1], &attr, do_max, argv);
  pthread_create(&workers[2], &attr, do_min, argv);

  /* Wait for all threads to terminate */
  for (int i = 0; i < 3; i++)
    pthread_join(workers[i], NULL);

  /* Output the results */
  printf("The average value is %d\n", avg);
  printf("The minimum value is %d\n", min);
  printf("The maximum value is %d\n", max);
}

/* Function Implmentations */
void* do_avg(void* param){

  int i, num_elem;
  char** arguments;
  avg = 0;
  num_elem = 0;
  
  /* Convert the void* to char* */
  arguments = param;
  
  /* Start at argv[1] */
  i = 1; 
  while (arguments[i] != NULL) {
    avg += atoi(arguments[i]);
    num_elem ++;
    i ++;
  }

  avg /= num_elem;

  pthread_exit(0);
}

void* do_max(void* param){

  int i, n;
  char** arguments;
  max = 0;
  
  /* Convert the void* to char* */
  arguments = param;
  
  /* Start at argv[1] */
  i = 1; 
  max = atoi(arguments[i]);
  i ++;
  while (arguments[i] != NULL) {
    if ((n = atoi(arguments[i])) > max)
      max = n;
    i ++;
  }

  pthread_exit(0);
}

void* do_min(void* param){
 
  int i, n;
  char** arguments;
  min = 0;
  
  /* Convert the void* to char* */
  arguments = param;
  
  /* Start at argv[1] */
  i = 1; 
  min = atoi(arguments[i]);
  i ++;
  while (arguments[i] != NULL) {
    if ((n = atoi(arguments[i])) < min)
      min = n;
    i ++;
  }
  
  pthread_exit(0);
}



