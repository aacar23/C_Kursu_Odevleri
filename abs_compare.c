#include <stdlib.h>

int abs_compare(const void *vp1, const void *vp2)
{
    unsigned int var1 = abs(*(const int *)vp1);
    unsigned int var2 = abs(*(const int *)vp2);

    if (var1 > var2)
        return 1;
    if (var1 < var2)
        return -1;

    return 0;
}