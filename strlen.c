#include <stddef.h>
size_t strlen_1(const char *p)
{
    size_t size = 0;
    while (*p++)
        size++;
    return size;
}