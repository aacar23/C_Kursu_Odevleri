#include <stdio.h>

void set_two_dimensional_array_random_generic_linux(void *vp, size_t bytes_of_smallest_element, const void *modulus_num, void *(*mod_func)(void *num, const void *mod), size_t rows, size_t columns)
{
    unsigned char *p = (unsigned char *)vp;
    FILE *f = fopen("/dev/urandom", "r");
    size_t size = rows * columns;
    do {
        for (size_t i = 0;i < bytes_of_smallest_element;i++)
            fread(p + i, 1, 1, f);
        (*mod_func)(p, modulus_num);
    } while (p += bytes_of_smallest_element, --size);
    fclose(f);
}