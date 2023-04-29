#include <stddef.h>

void swap_objects(void *a, void *b, size_t bytes)
{
    char *a_point = (char *)a;
    char *b_point = (char *)b;

    while (bytes--) {
        char temp = *a_point;
        *a_point++ = *b_point;
        *b_point++ = temp;
    }
}

void reverse_array(void *arr, size_t bytes_of_array, size_t bytes_of_array_element)
{
    char *start = (char *)arr;
    char *end = (char *)arr + bytes_of_array - bytes_of_array_element;

    do{
        swap_objects(start, end, bytes_of_array_element);
    }while ((start += bytes_of_array_element) < (end -= bytes_of_array_element));
}