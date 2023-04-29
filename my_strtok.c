#include <string.h>


int is_delimeter(int ch, const char *delimeter)
{
    size_t i;
    for (i = 0;*(delimeter + i) && ch != *(delimeter + i);i++)
        ;
    return i != strlen(delimeter);
}

char *find_start(char *str, const char *delimeter, const char **start)
{
    size_t i;
    for (i = 0;*(str + i) && is_delimeter(*(str + i), delimeter);i++)
        ;
    return i == strlen(str) ? NULL : (char *)(*start = str + i);
}

char *find_end(const char *delimeter, char *start, char **end, const char **following)
{
    size_t i;
    for (i = 0;*(start + i) && !is_delimeter(*(start + i), delimeter);i++)
        ;
    if (i != strlen(start)){
        *following = start + i + 1;
        *(*end = start + i) = '\0';
        return *end;
    }
    else if (*(start + i) == '\0') {
        *following = NULL;
        return *end = start + i;
    }
    return NULL;
}

char *strtok_capsulated(char *str, const char *delimeter, char **start, char **end, char **following)
{
    if (*following == NULL)
        return NULL;
    char *ret;
    if ((ret = find_start(str, delimeter, (const char **)start)) && find_end(delimeter, *start, end, (const char **)following))
        return ret;
    return NULL;
}


char *my_strtok(char *str, const char *delimeter)
{
    static char *following;
    static char *start;
    static char *end;
    if (str) {
        following = str;
        return strtok_capsulated(str, delimeter, &start, &end, &following);
    }
    return strtok_capsulated(following, delimeter, &start, &end, &following);
}