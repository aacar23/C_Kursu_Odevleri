#include <stdio.h>
void print_names(const char *const *names, size_t size)
{
    while (size--)
        printf("%s ", *(names + size));
    
    putchar('\n');
}