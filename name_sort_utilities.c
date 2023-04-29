
#include <string.h>

#define TYPE_SIZE 20

void swap_char_arrays(char (*ptr1)[TYPE_SIZE], char (*ptr2)[TYPE_SIZE]) {
    for (size_t i = 0; i < TYPE_SIZE; i++){
        int temp = *(*ptr1 + i);
        *(*ptr1 + i) = *(*ptr2 + i);
        *(*ptr2 + i) = temp;
    }
}


char (*get_min_element(const char (*arr)[TYPE_SIZE], size_t size))[TYPE_SIZE]
{
    const char (*min)[TYPE_SIZE] = arr;
    while (size--)
        if (strcmp(*(arr + size), *min) < 0)
            min = arr + size;
    return (char (*)[TYPE_SIZE])min;
}


char (*pivot_partation(char (*arr)[TYPE_SIZE], size_t size))[TYPE_SIZE]
{
    char (*start)[TYPE_SIZE] = arr;
    char (*end)[TYPE_SIZE] = arr + size - 1;
    char (*pivot)[TYPE_SIZE] = start;
    while (start < end){
        if (strcmp(*start, *end) < 0)
            swap_char_arrays(pivot++, start);
        start++;
    }
    swap_char_arrays(pivot, end);
    return pivot;
}

void qsort_names(char (*arr)[TYPE_SIZE], size_t size)
{
    char (*start)[TYPE_SIZE] = arr;
    char (*end)[TYPE_SIZE] = arr + size - 1;
    if (start < end){
        char (*pivot)[TYPE_SIZE] = pivot_partation(arr, size);

        qsort_names(pivot + 1, end - pivot);
        qsort_names(arr, pivot - arr);
    }
}


void bsort_names(char (*arr)[TYPE_SIZE], size_t size)
{
    for (size_t i = 0;i < size - 1;i++)
        for (size_t k = 0;k < size - i - 1;k++)
            if (strcmp(*(arr + k), *(arr + k + 1)) > 0)
                swap_char_arrays(arr + k, arr + k + 1);


}

void selection_sort_names(char (*arr)[TYPE_SIZE], size_t size)
{
    for (size_t i = 0;i < size - 1;i++)
        swap_char_arrays(arr + i, get_min_element(arr + i, size - i));
}