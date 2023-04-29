#include <stdio.h>
#include <stdlib.h>

int endiannes(void)
{
    unsigned int a = 254;
    unsigned char *pointer_of_a = (unsigned char *)&a;
    unsigned int a_copy = 0;
    int multiplier = 1;
    size_t bytes = sizeof(int);
    do {
        a_copy += *pointer_of_a++ * multiplier;
    } while (multiplier *= 256, --bytes);
    return a_copy == a ? LITTLE_ENDIAN : BIG_ENDIAN;
}


int main(void)
{
    if (endiannes())
        printf("the system uses little endian");
    else if (!endiannes())
        printf("the system uses big endian");
}