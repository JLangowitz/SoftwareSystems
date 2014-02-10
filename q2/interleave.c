// Interleave program for SofSys
// Quiz 2
// Josh Langowitz
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *interleave(char *s1, char *s2)
{
    int l1 = strchr(s1, '\0') - s1;
    int l2 = strchr(s2, '\0') - s2;
    int length= l1 + l2;
    printf("%i %i\n", l1, l2);
    char* interleaved = malloc((length+1)*sizeof(char));
    int s1next = 1; 
    int s1count = 0;
    int s2count = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        if (s1next && (s1count < l1))
        {
            interleaved[i]=s1[s1count];
            s1count++;
        }
        else if (s1next && (s2count < l2))
        {
            interleaved[i]=s2[s2count];
            s2count++;
        }
        s1next = 1 - s1next;
    }
    return interleaved;
}

int main()
{
    char word1[] = "clips";
    char word2[] = "aloe";
    // interleave(word1,word2);
    char *word = interleave(word1,word2);
    printf("%s\n", word);
    return 0;
}
