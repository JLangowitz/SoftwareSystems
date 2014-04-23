#include <stdint.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    uint8_t most = 1;
    uint8_t least = 2;
    uint16_t res;
    res = (most << 8) + least;
    printf("%i\n", res);
}