#include <stdlib.h>
#include <string.h>

char *str_sum_array(const char * const *str_arr, size_t size)
{
    size_t len = 0;

    for (size_t i = 0;i < size;i++)
        len += strlen(*(str_arr + i));

    char *res = malloc(sizeof(char) * len + 1);
    if (!res)
        return NULL;
    *res = '\0';

    for (size_t i = 0;i < size;i++)
        strcat(res, *(str_arr + i));

    return res;
}