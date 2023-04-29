#include <stdlib.h>
#include <string.h>

void* mymemmove(void *dest, const void * src, size_t size)
{
    unsigned char *src_copy = (unsigned char *)malloc(sizeof(unsigned char) * size);
    unsigned char *pdest = (unsigned char *)dest;
    memcpy(src_copy, src, size);
    while (size--)
        *pdest++ = *src_copy++;
    return dest;
}