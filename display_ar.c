#include <stdio.h>

void display_ar(const int (*ptr)[5], size_t size)
{
    while (size--) {
        for (int i = 0; i < 5; i++)
            printf("%d ", *(*ptr + i));
        putchar('\n');
        ptr++;
    }
}