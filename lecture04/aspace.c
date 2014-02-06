/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int global;
int global2;

int main ()
{
    int local = 5;
    int local2 = 1;
    void *p = malloc(128);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of global is %p\n", &global2);
    printf ("Address of local is %p\n", &local);
    printf ("Address of local2 is %p\n", &local2);
    printf ("Address of p is %p to %p\n", p, &p[128]);
    
    return 0;
}
