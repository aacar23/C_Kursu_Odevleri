#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *str_duplicated(const char *str)
{
    char *dup = malloc(sizeof(char) * (strlen(str) + 1));
    if (!dup){
        fprintf(stderr, "out of memory");
        exit(1);
    }
    strcpy(dup, str);
    return dup;
}