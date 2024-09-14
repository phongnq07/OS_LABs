/*
   This is a simple program to initial rand numbers
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50

int main () {
   int i, n;
   time_t t;
   
      
   /* Intializes random number generator */
   srand((unsigned) time(&t));

   /* Print 5 random numbers from 0 to 99 */
   printf("\n The random numbers of (0-99) : \n");
   for( i = 1 ; i < N ; i++ ) {
      printf("%4d", rand() % 100);
      if(i % 10 == 0) printf("\n");
   }
   
   printf("\n");
   return(0);
}