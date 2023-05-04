#include <string.h>

char *my_strncpy(char *p1, const char *p2, size_t size)
{
    char *ret_p1 = p1;
    do {
        *p1++ = *p2++;
    } while (--size && *p2);
    while (size--)
        *p1++ = '\0';
    return ret_p1;
}

char *my_strncat(char *p1, const char *p2, size_t size)
{
    char *ret_p1 = p1;
    p1 += strlen(p1);
    while (size-- && *p2) {
        *p1++ = *p2++;
    }

    *p1 = '\0';
    return ret_p1;
}

int my_strncmp(const char *p1, const char *p2, size_t size)
{
    const unsigned char *temp_p1 = (const unsigned char *)p1;
    const unsigned char *temp_p2 = (const unsigned char *)p2;
    do{
        if (*temp_p1 != *temp_p2)
            return *temp_p1 - *temp_p2;
    } while (temp_p1++, temp_p2++, --size);
    return 0;
}