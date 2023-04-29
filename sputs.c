#include <stdio.h>

void sputs(const char *str)
{
    while (putchar(*str), *str++)
        ;
}