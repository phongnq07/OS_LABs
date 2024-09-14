/* Compute matrix sum by threads */
/* Tinh toan ma tran */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4

int A[N][N], sum[N];

void *thr_func(void *arg) {
    int j;
    
    pthread_t tid = pthread_self(); //get thread ID number
    
    int row = (*(int *) arg);
    
    
    printf("Thread %ld \n", tid);
    printf("Print Line# %d : \n ", row);
    
    int sum = 0;
    for(j=0; j < N; j++) {
        sum += A[row][j];        
        printf("%4d", A[row][j]);
    }
    
    printf("\n");   

    printf("Sum of line %d is %d\n", row, sum); 
    pthread_exit((void *)0); //thread exit: 0 = normal terminal   
}

int main(int argc, char *argv[])
{
    pthread_t thread[N]; //thread IDs
    
    
    int i, j, r, total = 0;
    
    void* status;
    
    printf("Main: initialize A matrix \n");
    for(i=0; i < N; i++) {
        sum[i] = 0;
        for(j=0; j < N; j++) {
            A[i][j] = i*N + j + 1;
            printf("%4d", A[i][j]);
        }
        printf("\n");
    }

    int threadNum = 0;
    int rc;

    i = 0;
    while( i < N) {
        threadNum = i;
        rc = pthread_create(&thread[threadNum], NULL, &thr_func, &threadNum);        
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        pthread_join(thread[i], &status);
        i++;                 
    }   

    pthread_exit(NULL);
}
