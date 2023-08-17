#include <string.h>
#include <stdlib.h>

void gswap(void *vp1, void *vp2, size_t bytes)
{
    unsigned char *p1 = (unsigned char *)vp1;
    unsigned char *p2 = (unsigned char *)vp2;
    while (bytes--) {
        unsigned char temp = *p1;
        *p1++ = *p2;
        *p2++ = temp;
    }
}



void *mymemset(void *vp, int val, size_t bytes)
{
    unsigned char *p = (unsigned char *)vp;
    while (bytes--)
        *p++ = val;
    return vp;
}

int mymemcmp(const void *vp1, const void *vp2, size_t bytes)
{
    int temp_size = (int)bytes;
    const unsigned char *p1 = (const unsigned char *)vp1;
    const unsigned char *p2 = (const unsigned char *)vp2;
    while (temp_size-- && *p1 == *p2)
        p1++, p2++;
    return temp_size >= 0 ? (int)*p1 - (int)*p2 : 0;
}


int signed_mymemcmp(const void *vp1, const void *vp2, size_t bytes)
{
    int temp_size = (int)bytes;
    const signed char *p1 = (const signed char *)vp1;
    const signed char *p2 = (const signed char *)vp2;
    while (temp_size-- && *p1 == *p2)
        p1++, p2++;
    return temp_size >= 0 ? (int)*p1 - (int)*p2 : 0;
}


void *signed_array_min_element(void *vp, size_t bytes_of_array, size_t bytes_of_element)
{
    const signed char *p = (const signed char *)vp;
    const signed char *min = p;
    do{
        if (signed_mymemcmp(p, min, bytes_of_element) < 0)
            min = p;
    } while (p += bytes_of_element, bytes_of_array -= bytes_of_element);
    return (void *)min;
}

void *unsigned_array_min_element(void *vp, size_t bytes_of_array, size_t bytes_of_element)
{
    const unsigned char *p = (const unsigned char *)vp;
    const unsigned char *min = p;
    do{
        if (memcmp(p, min, bytes_of_element) < 0)
            min = p;
    } while (p += bytes_of_element, bytes_of_array -= bytes_of_element);
    return (void *)min;
}


void *mymemchr(const void *vp1, int ch, size_t bytes)
{
    const unsigned char *p1 = (const unsigned char *)vp1;
    while (bytes--) {
        if (*p1 == (unsigned) ch)
            return (void *) p1;
        p1++;
    }
    return NULL;
}

void *mymemcpy(void *vpdest, void *vpsource, size_t bytes)
{
    unsigned char *pdest = (unsigned char *)vpdest;
    unsigned char *psource = (unsigned char *)vpsource;
    while (*pdest++ = *psource++,--bytes)
        ;
    return vpdest;
}

void *necmemmove(void *vpdest, const void *vpsource, size_t bytes)
{
    unsigned char *pdest = (unsigned char *)vpdest;
    const unsigned char *psource = (const unsigned char *)vpsource;
    if (pdest > psource){
        pdest += bytes;
        psource += bytes;
        while (*--pdest = *--psource, --bytes)
            ;
        return vpdest;
    }
    while (*pdest++ = *psource++, --bytes)
        ;
    return vpdest;
}

void *mymemmove(void *vpdest, const void *vpsource, size_t bytes)
{
    const unsigned char *psource = (const unsigned char *)vpsource;
    unsigned char *psource_copy = (unsigned char *)malloc(bytes);
    unsigned char *pdest = (unsigned char *)vpdest;
    memcpy(pdest, memcpy(psource_copy, psource, bytes), bytes);
    free(psource_copy);
    return vpdest;
}


void *nec_reverse_array(void *vp, size_t bytes_of_array, size_t bytes_of_element)
{
    unsigned char *p = (unsigned char *)vp;
    for (size_t i = 0;i < bytes_of_array / 2;i += bytes_of_element)
        gswap(p + i, p + bytes_of_array - i - bytes_of_element, bytes_of_element);
    return vp;
}

void *my_reverse_array(void *vstart, void *vend, size_t bytes_of_element)
{
    unsigned char *start = (unsigned char *)vstart;
    unsigned char *end = (unsigned char *)vend;
    do{
        gswap(start, end, bytes_of_element);
    } while ((start += bytes_of_element) < (end -= bytes_of_element));
    return vstart;
}


void *array_search(const void *vp, const void *val_p, size_t bytes_of_array, size_t bytes_of_element)
{
    const unsigned char *p = (const unsigned char *)vp;
    const unsigned char *val = (const unsigned char *)val_p;
    do {
        if (!memcmp(p, val, bytes_of_element))
            return (void *) p;
        p += bytes_of_element;
    } while (bytes_of_array -= bytes_of_element);
    return NULL;
}

void *unsigned_pivot_partation(void *vstart, void *vend, size_t bytes_of_element)
{
    unsigned char *start = (unsigned char *)vstart;
    unsigned char *end = (unsigned char *)vend;
    unsigned char *pivot = start;
    while (start < end){
        if (memcmp(start, end, bytes_of_element) < 0){
            gswap(pivot, start, bytes_of_element);
            pivot += bytes_of_element;
        }
        start += bytes_of_element;
    }
    gswap(pivot, end, bytes_of_element);
    return (void *)pivot;
}




void* quick_sort_unsigned(void *vstart, void *vend, size_t bytes_of_element)
{
    unsigned char *start = (unsigned char *)vstart;
    unsigned char *end = (unsigned char *)vend;
    if (start < end){
        unsigned char *pivot = (unsigned char *) unsigned_pivot_partation(vstart, vend, bytes_of_element);

        quick_sort_unsigned(pivot + bytes_of_element, vend, bytes_of_element);
        quick_sort_unsigned(vstart, pivot - bytes_of_element, bytes_of_element);
    }
    return vstart;
}

void *signed_pivot_partation(void *vstart, void *vend, size_t bytes_of_element)
{
    signed char *start = (signed char *)vstart;
    signed char *end = (signed char *)vend;
    signed char *pivot = start;
    while (start < end){
        if (signed_mymemcmp(start, end, bytes_of_element) < 0){
            gswap(pivot, start, bytes_of_element);
            pivot += bytes_of_element;
        }
        start += bytes_of_element;
    }
    gswap(pivot, end, bytes_of_element);
    return (void *)pivot;
}




void* quick_sort_signed(void *vstart, void *vend, size_t bytes_of_element)
{
    signed char *start = (signed char *)vstart;
    signed char *end = (signed char *)vend;
    if (start < end){
        signed char *pivot = (signed char *)signed_pivot_partation(vstart, vend, bytes_of_element);

        quick_sort_signed(pivot + bytes_of_element, vend, bytes_of_element);
        quick_sort_signed(vstart, pivot - bytes_of_element, bytes_of_element);
    }
    return vstart;
}

void *unsigned_bubble_sort(void *vp, size_t bytes_of_array, size_t bytes_of_element)
{
    unsigned char *p = (unsigned char *)vp;
    for (size_t i = 0;i < bytes_of_array - bytes_of_element;i += bytes_of_element)
        for (size_t t = 0;t < bytes_of_array - bytes_of_element - i;t += bytes_of_element)
            if (memcmp(p + t, p + t + bytes_of_element, bytes_of_element) > 0)
                gswap(p + t, p + t + bytes_of_element, bytes_of_element);
    return vp;
}


void *signed_bubble_sort(void *vp, size_t bytes_of_array, size_t bytes_of_element)
{
    signed char *p = (signed char *)vp;
    for (size_t i = 0;i < bytes_of_array - bytes_of_element;i += bytes_of_element)
        for (size_t t = 0;t < bytes_of_array - bytes_of_element - i;t += bytes_of_element)
            if (signed_mymemcmp(p + t, p + t + bytes_of_element, bytes_of_element) > 0)
                gswap(p + t, p + t + bytes_of_element, bytes_of_element);
    return vp;
}

void *unsigned_selection_sort(void *vp, size_t bytes_of_array, size_t bytes_of_element)
{
    unsigned char *p = (unsigned char *)vp;
    for (size_t i = 0;i < bytes_of_array - bytes_of_element; i+= bytes_of_element)
        gswap(p + i, unsigned_array_min_element(p + i + bytes_of_element, bytes_of_array - bytes_of_element - i, bytes_of_element), bytes_of_element);
    return vp;
}

void *signed_selection_sort(void *vp, size_t bytes_of_array, size_t bytes_of_element)
{
    signed char *p = (signed char *)vp;
    for (size_t i = 0;i < bytes_of_array - bytes_of_element; i+= bytes_of_element)
        gswap(p + i, signed_array_min_element(p + i + bytes_of_element, bytes_of_array - i - bytes_of_element, bytes_of_element), bytes_of_element);
    return vp;
}

