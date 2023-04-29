#include <stddef.h>
void* mymemset(void *vp, int val, size_t sz)
{
    char *p = (char *)vp;
    while (sz--)
        *p++ = (char)val;
    return vp;
}
