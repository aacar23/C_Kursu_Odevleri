#include <stddef.h>

void* bsearch(const void *vkey, const void *vp, size_t count, size_t size, int (*comp)(const void*, const void*))
{
    size_t idx_first = 0;
    size_t idx_last = count - 1;

    const char *p = (const char *)vp;
    const char *key = (const char *)vkey;

    while (idx_first <= idx_last){
        size_t idx_mid = (idx_first + idx_last) / 2;

        if (!(*comp)(p + idx_mid * size, key))
            return (void *)p + idx_mid * size;

        if ((*comp)(p + idx_mid * size, key) > 0)
            idx_last = idx_mid - 1;
        else
            idx_first = idx_mid + 1;
    }
    return NULL;
}