#include <stdio.h>

char *str_end(const char *str)
{
    char *end;
    while(*(end = (char *)str++))
        ;
    return end;

}


char *mystrstr(const char *s1, const char *s2)
{
    const char *start;
    const char *s2_end = str_end(s2);
    const char *end;
    for (int i = 0;*(s1 + i);i++)
        if (*(s1 + i) == *s2)
            start = s1 + i;
    for (int i = 0;*(s1 + i);i++)
        if (*(s1 + i) == *s2_end)
            end = s1 + i;
    for (int i = 0;start + i <= end;i++)
        if (*(start + i) != *(s2 + i))
            return NULL;
    return (char *)start;


}

int main(void)
{
    char str[] = "You can only be afraid of what you think you know";
    char *p = mystrstr(str, "be");

    if (p) {
        printf("bulundu...indis = (%tu) (%s)\n", p - str, p);
    }
    else {
        printf("bulunamadi\n");
    }
}