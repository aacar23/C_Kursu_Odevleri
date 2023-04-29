#include <stdio.h>
#include <string.h>

char *removeStr(char *ptr, const char *p)
{
    size_t p_size = strlen(p);
    int write_idx = 0;
    for (size_t i = 0, k = 0;*(ptr + i);i++) {
        if (*(ptr + i) != *(p + (k % p_size))) {
            *(ptr + write_idx++) = *(ptr + i);
        }
        else{
            k++;
        }
    }
    *(ptr + write_idx) = '\0';
    return ptr;
}

int main()
{
    char s1[] = "bugun pazartesi gunu";
    char s2[] = "ali 2345metin 2345";

    puts(removeStr(s1, "tesi")); // bugun pazar gunu
    puts(removeStr(s2, "2345")); //ali metin 2345
}