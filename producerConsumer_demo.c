#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define N 100
typedef struct Buffer {
    int n;
    int a[N];
} Buffer;

void EnterValue(Buffer *ptrb);

int main(void)
{
    pid_t pid;
    int status;
    Buffer b;

    // Get and print my own pid, then fork and check for errors
    printf("My PID is %d\n", getpid());
    EnterValue(&b);

    if((pid = fork()) == -1) {
        perror("Can't fork");
        return 1;
    }

    if (pid == 0) {        
        //if pid is 0 we are in the child process,
        //from here we execute 'man ls'
        printf("\nChild process read :\n");
        for(int i =0; i < b.n; i++) printf("%3d", b.a[i]);
        printf("\n");
    }
    else if(pid > 0) {
            //In the parent we must wait for the child to exit with waitpid().
            //Afterward, the child exit status is written to 'status'            
            waitpid(pid, &status, 0);
            printf("Child executed with PID %d\n", pid);
            printf("Its return status was %d\n",status);           
        }
        else {
            fprintf(stderr, "Something went wrong forking\n");
            return 1;
        }    
    return 0;
}

void EnterValue(Buffer *ptrb) {
    printf("\nParent produce item int for Child Consumer \n");
    printf("Enter N = ");
    scanf("%d", &ptrb->n);
    for(int i = 0; i < ptrb->n; i++) {
        printf("a[%d] = ", i);
        scanf("%d", &ptrb->a[i]);
    }
}