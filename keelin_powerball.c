#include <stdio.h>
#include <stdlib.h>

void draw(int pb[]); 

int main(int argc, char* argv[])
{
  int seeds[10];
  int powerballs[6]; 
  int i, j;

  seeds[0] = 93371; 
  for (i = 1; i < 10; i++) {
    seeds[i] += 93383; 
  }

  /* Draw 10 times. */
  for (i = 0; i < 10; i++) {
    srand(seeds[i]);
    draw(powerballs);
    
    printf("Week %d:\n", i + 1);
    printf("White numbers:\t");
    for (j = 0; j < 5; j++) {
      printf("%7d", powerballs[j]);
    }
    printf("\tRed number:%d\n\n", powerballs[5]);
  }
  
  return 0; 
}

void draw(int pb[])
{
  int i, j, ran;
  
  /* Draw 5 white numbers. */
  for (i = 0; i < 5; i++) {
    ran = (rand() % 69) + 1;  
    
    /* Keep calling rand() if ran is a duplicate. */
    /* Check with all the previously drawn numbers
       everytime a number is drawn. */
    j = 0;
    while (j != i) {
      if (ran == pb[j]) {
	ran = (rand() % 69) + 1;
	j = 0; 
      } else {
	j++;
      }
    }
    /* Keep the number. */
    pb[i] = ran;
  }

  /* Draw a red number. */
  ran = (rand() % 26) + 1;  
  /* Keep the number. */
  pb[i] = ran;  
}
