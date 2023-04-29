#include <stddef.h>
void* mymemcpy(void *pdest, const void *psource, size_t n)
{
    const char *source = (const char *)psource;
    char *dest = (char *)pdest;
    while (n--)
        *dest++ = *source++;
    return pdest;
}