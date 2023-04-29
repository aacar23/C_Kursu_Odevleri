#include <stdio.h>
char *remove_char(char *str, char ch)
{
    int write_idx = 0;
    for (int i = 0;*(str + i);i++)
        if (*(str + i) != ch)
            *(str + write_idx++) = *(str + i);
    *(str + write_idx) = '\0';
    return str;
}

int main()
{
    char str[] = "babama bak babama";

    puts(remove_char(str, 'a')); //bbm bk bbm
    puts(remove_char(str, 'b')); //m k m
    puts(remove_char(str, ' ')); //mkm
    puts(remove_char(str, 'm')); //k;
}