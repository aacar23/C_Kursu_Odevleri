#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}
void reverse(char *start, char *end)
{
    while (start < end){
        swap(start++, end--);
    }
}
char * reverseWords(char * s){
    char *s_real = s;
    char *start = s;
    char *end = 0;
    do{
        if (isspace(*s)){
            end = s - 1;
            reverse(start, end);
            start = s + 1;
        }
        s++;
    }while (*s);
    reverse(start, s_real + strlen(s_real) - 1);
    
    return s_real;
}