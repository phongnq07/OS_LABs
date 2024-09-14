/*
    This is a program generate a random numbers with argument from command lines
    $rand-numbers-args [the number of elements in array]
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define N 100

int a[N];

void *thr1_func(void *arg);
void *thr2_func(void *arg);

int main(int argc, char* argv[])
{
    pthread_t tid1, tid2; 
    // tid1 : create random number of elements in a array

    if(argc != 2) {
        printf("Usage : %s <number of elements in array>\n", argv[0]);
        exit(1);
    }

    int numArr = atoi(argv[1]);

    pthread_create(&tid1, NULL, thr1_func, &numArr);
    pthread_create(&tid2, NULL, thr2_func, &numArr);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 1;
}

void *thr1_func(void *arg) {
    time_t t;
    srand((unsigned) time(&t));

    int *num = (int *) arg;
    for(int i=0; i < *num; i++) a[i] = rand() % 100;

    for(int i=1; i <= *num; i++) {
        printf("%4d",a[i-1]);
        if(i % 10 == 0) printf("\n");
    }

    pthread_exit(NULL);
}

void *thr2_func(void *arg) {
    int *num = (int *) arg;

    printf("\nThread performed a even element selection.");
    printf("\nEven elements in array is : \n");

    for(int i=0; i < *num; i++)
        if(a[i] % 2 == 0) printf("%4d",a[i]);

    printf("\n");    
    pthread_exit(NULL);
}