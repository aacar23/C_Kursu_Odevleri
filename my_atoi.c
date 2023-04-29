#include <ctype.h>

int my_atoi(const char *str)
{
    int sum = 0;
    int sign = 1;
    int previous = 0;
    do{
        if (!isspace(*str))
            break;
    } while (*++str);

    if ((*str == '+') - (*str == '-')){
        sign = (*str == '+') - (*str == '-');
        str++;
    }

    for (int i = 0;isdigit(*(str + i));previous = sum += *(str + i++) - '0')
        if (previous)
            sum *= 10;
    return sign * sum;
}