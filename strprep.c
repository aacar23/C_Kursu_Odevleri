#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define		SIZE		200

void copy(char *dest, const char *from)
{
    int i;
    for (i = 0; *(from + i);i++)
        *(dest + i) = *(from + i);
    *(dest + i) = '\0';
}

char *strprep(char *p1, const char *p2)
{
    char *temp_p1 = malloc(sizeof(char) * (strlen(p1) + 1));
    copy(temp_p1, p1);
    int i;
    int k;
    for (i = 0;*(p2 + i);i++)
        *(p1 + i) = *(p2 + i);
    for (k = 0;*(temp_p1 + k);k++)
        *(p1 + i + k) = *(temp_p1 + k);
    *(p1 + i + k) = '\0';
    free(temp_p1);
    return p1;
}

int main(void)
{
    char s1[SIZE];
    char s2[SIZE];

    printf("iki yazi girin : "); //tayyip recep
    scanf("%s%s", s1, s2);
    puts(strprep(s1, s2)); //receptayyip
}