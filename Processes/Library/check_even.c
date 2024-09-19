/**
 * $gcc -Wall -fPIC -c even.c
 * $file even.o
 * Create static library
 * $ar rc even.a even.o
 * $gcc check_even.c even.a -o check_even
 * $./check_even 12
 * 
 * Create dynamic library
 * $gcc -shared -Wl,-soname,libeven.so -o libeven.so.1 even.o
 * $nm -D libeven.so.1
 * $sudo cp libeven.so.1 /usr/lib
 * $sudo ldconfig
 * $gcc check_even.c -o check_even -leven
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "even.h"

int main(int argc, char *argv[]) 
{
   long int num;

    /* Only one argument is accepted */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s number\n", argv[0]);
        return 1;
    }

    /* Only numbers 0-9 are accepted */
    if ( strspn(argv[1], "0123456789") != strlen(argv[1]) ) {
        fprintf(stderr, "Only numeric values are accepted\n");
        return 1;
    }

    num = atol(argv[1]); /* String to long */

    if (isEven(num))  /* Check if num is a even number */   
        printf("%ld is a even number\n", num);    
    else 
        printf("%ld is not a even number\n", num);   
    
    return 0;
}