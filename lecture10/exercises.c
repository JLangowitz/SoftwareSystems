// Josh Langowitz
// Lecture 10 Exercises
// SofSys Spring14
// 2/24/14
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int twos_comp (int x);
int low_bits (int x, int n);
int unpack_double (double x);

int twos_comp (int x){
    return (x^-1)+1;
}

int low_bits (int x, int n){
    uint8_t mask = 1;
    mask = (mask << n) - 1;
    return x & mask;
}

int unpack_double (double x){
    union {
        double d;
        unsigned long int u;
    } p;

    p.d = x;
    unsigned long int sign = (p.u >> 63) & 1;
    unsigned long int exponent = (p.u >> 52) & ((1 << 11) - 1);
    unsigned long int coef = p.u & ((1 << 52) - 1);
    printf("%d\n%d\n%d\n", sign, exponent, coef);
}

int main(int argc, char const *argv[])
{
    printf("%i\n", twos_comp(100));
    printf("%i\n", low_bits(9,3));
    unpack_double(1.1)
    return 0;
}