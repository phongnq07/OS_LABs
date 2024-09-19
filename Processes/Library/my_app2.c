/*
    Author : Phong Nguyen Quoc
    step 1 : Recompile func-add, func-sub, func-mul, func-div with options : -Wall -fPIC
    //fPIC or fpic means "position independent code" generation a requirement for shared libraries

    $gcc -Wall -fPIC -c func-add.c // func-sub, func-mul, func-div
    then, func-add.o, func-sub.o, func-mul.o, func-div.o
    
    step 2 : Create a shared object (.so file) 
    $gcc -shared -o my_dlibmath.so func-add.o func-sub.o func-mul.o func-div.o
    then, we have a my_dlibmath.so - a shared object
    
    step 3 : copy a shared object (my_dlibmath.so) into /usr/lib
    $sudo cp my_dlibmath.so /usr/lib
    $sudo ldconfig

    step 4 : compile my_app2.c
    $gcc -c my_app2.c

    $ldd ./my_app2
*/

#include <stdio.h>
#include "my_dlibmath.h"

int main(void)
{
    int result;
    double dresult;

    result = add(3,2);
    printf("3 + 2 = %d\n",add(3,2));

    result = sub(3,2);
    printf("3 - 2 = %d\n",sub(3,2));

    result = mul(3,2);
    printf("3 * 2 = %d\n",mul(3,2));

    dresult = mydiv(3,2);
    printf("3 / 2 = %4.2lf\n",mydiv(3,2));
    return 0;
}
