#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *str_sum_buffer(const char *str1, const char *str2, char *buffer)
{
    strcpy(buffer, str1);
    strcat(buffer, str2);
    return buffer;
}


static char sum_static[512];

char *str_sum_static(const char *str1, const char *str2)
{
    strcpy(sum_static, str1);
    strcat(sum_static, str2);
    return sum_static;
}


char *str_sum_allocated(const char *str1, const char *str2)
{
    char *sum_allocated = (char *)malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    if (!sum_allocated){
        fprintf(stderr, "out of memory");
        return NULL;
    }
    strcpy(sum_allocated, str1);
    strcat(sum_allocated, str2);
    return sum_allocated;
}