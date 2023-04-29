#include <stddef.h>
void copy_str(char *pdest, size_t size, const char *psource)
{
    while (--size)
        *pdest++ = *psource++;
    *pdest= '\0';
}