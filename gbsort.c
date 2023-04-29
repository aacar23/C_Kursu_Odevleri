#include <stddef.h>

void gswap(void *vp1, void *vp2, size_t bytes)
{
    char *p1 = (char *)vp1;
    char *p2 = (char *)vp2;
    while (bytes--){
        int temp = *p1;
        *p1++ = *p2;
        *p2++ = temp;
    }
}

void gbsort(void *vp, size_t count, size_t bytes_of_element, int (*fp)(const void *, const void *))
{
    char *p = (char *)vp;
    for (size_t i = 0;i < count - 1;i++)
        for (size_t k = 0; k < count - 1 - i; k++)
            if ((*fp)(p + k * bytes_of_element, p + k * bytes_of_element + bytes_of_element) > 0)
                gswap(p + k * bytes_of_element, p + k * bytes_of_element + bytes_of_element, bytes_of_element);
}