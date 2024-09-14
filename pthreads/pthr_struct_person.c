#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct Person {
    char name[30];
    char msg[64];
} Person;


static void *print_a_Struct(void *args) {
    Person *p = (Person *) args; // Note How to cast 

    printf ("Hello World! I am: %s!\n", p->name);
    printf ("%s!\n", p->msg);

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thrID;
    int ret;
    long i = 0;
    Person per;

    memset(&per, 0x0, sizeof(Person));
    strncpy(per.name, "Phong Nguyen Quoc", sizeof(per.name));
    strncpy(per.msg, "I am a new thread", sizeof(per.msg));
	
    ret = pthread_create(&thrID, NULL, print_a_Struct, (&per));

    if(ret) {
        printf("pthread_create() error number is %d\n", ret);
        return -1; 
    }

    pthread_exit(NULL);
}