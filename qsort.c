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

int int_compare(const void *vp1, const void *vp2)
{
    const int *p1 = (const int *)vp1;
    const int *p2 = (const int *)vp2;
    return *p1 < *p2;
}

void *pivot_partation(void *vstart, void *vend, size_t bytes, int (*compare_function)(const void *, const void *))
{
    char *start = (char *)vstart;
    char *end = (char *)vend;
    char *pivot = start;
    while (start < end){
        if ((*compare_function)(start, end)){
            gswap(pivot, start, bytes);
            pivot += bytes;
        }
        start += bytes;
    }
    gswap(pivot, end, bytes);
    return pivot;
}


void qsort(void *vpa, size_t count, size_t bytes_of_element, int (*compare_function)(const void *, const void *))
{
    #define end (pa + (count - 1) * (bytes_of_element))
    #define call_1_size ((pivot - pa) / bytes_of_element)
    #define call_2_size ((end - pivot) / bytes_of_element)

    char *pa = (char *)vpa;
    if (pa < end){
        char *pivot = (char *)pivot_partation(vpa, end, bytes_of_element, compare_function);

        qsort(pa, call_1_size, bytes_of_element, compare_function);
        qsort(pivot + bytes_of_element, call_2_size, bytes_of_element, compare_function);
    }

    #undef end
    #undef call_1_size
    #undef call_2_size
}