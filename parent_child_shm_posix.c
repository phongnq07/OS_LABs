#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

#define N 10
int n;

#define SHM_NAME "/my_shm"
#define SHM_SIZE 1024

void InputBuffer(void *ptr);

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    void *ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        InputBuffer(ptr);
        void *ptr_child = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (ptr_child == MAP_FAILED) {
            perror("mmap");
            exit(1);
        }

        //printf("Child read: %s\n", (char *) ptr_child);
        printf("Child read : ");
       
        for(int i=0; i < n; i++) printf("%3d", *((int *) ptr_child + i) );
        printf("\nChild finished\n");

        if (munmap(ptr_child, SHM_SIZE) == -1) {
            perror("munmap");
            exit(1);
        }
    } else {
        //sprintf((char *) ptr, "Hello from parent!");
        //printf("Parent wrote: %s\n", (char *) ptr);  
        //InputBuffer(ptr);     
        
        if (wait(NULL) == -1) {
            perror("wait");
            exit(1);
        }
    }

    if (munmap(ptr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }

    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
        exit(1);
    }

    return 0;
}

void InputBuffer(void *ptr) {
    //int n;
    time_t t;
    srand((unsigned) time(&t));

    do {
        printf("Enter N < %d - N = ", N);
        scanf("%d", &n);
    } while(n > N);
    
    printf("\nParent produce items for child : ");
    for(int i=0; i < n; i++) { 
        *((int *) ptr+i) = rand() % 50;
        printf("%3d", *((int *)ptr+i));
    }
    printf("\n");   
}
