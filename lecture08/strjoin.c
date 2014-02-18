/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin(char *array[], int n)
{
    int len = 0;
    int i;
    char *joined;
    for (i = 0; i < n; i++){
        len += strlen(array[i]);
    }
    joined = malloc(len*sizeof(char));
    joined[0] = '\0';
    for (i = 0; i < n; i++){
        strcat(joined, array[i]);
    }
    return joined;
}


int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("%s\n", s);
    return 0;
}
