#include <ctype.h>
#include <string.h>


#define OCTAL 8
#define HEX 16
#define DEC 10


int is_base(int ch, int base)
{
    const char number_chars[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    for (int i = 0;i < base;i++)
        if (toupper(ch) == number_chars[i])
            return 1;


    return 0;
}



int strncmp_case_insensitive(const char *str1, const char *str2, size_t n)
{
    do{
        if (toupper(*str1) != toupper(*str2))
            return toupper(*str1) - toupper(*str2);
    } while (*++str1 && *++str2 && --n);


    return 0;
}



long my_strtol_core(const char *str, char **end, int base)
{
    const char *start = str;
    long sum = 0;


    do{
        if (*str != '\x20' && is_base(*str, base))
            break;
        else if(*str != '\x20'){
            if (end)
                *end = (char *)start;
            return sum;
        }
    } while (*++str);


    do{
        if (*str != '0')
            break;
    } while (*++str);


    do{
        if (is_base(*str, base)){
            if (isdigit(*str))
                sum = sum * base + *str - '0';
            else if(base > 10 && is_base(*str, base))
                sum = sum * base + toupper(*str) - 'A' + 10;
        }
        else {
            if (end)
                *end = (char *)str;
            return sum;
        }
    } while (*++str);


    if (end)
        *end = (char *)str;
    return sum;
}



long my_strtol_base_0(const char *str, char **end)
{
    do{
        if (*str == '0'){
            if (strlen(str) > 2 && toupper(*(str + 1)) == 'X' && isxdigit(*(str + 2)))
                return my_strtol_core(str + 2, end, HEX);
            return my_strtol_core(str, end, OCTAL);
        }
        if (isdigit(*str))
            return my_strtol_core(str, end, DEC);
        if (*str != '\x20')
            return 0l;
    } while (*++str);


    return 0l;
}



long my_strtol_base_16(const char *str, char **end)
{
    do{
        if (!strncmp_case_insensitive(str, "0x", 2) && isxdigit(*(str + 2)))
            return my_strtol_core(str + 2, end, HEX);
        if (isxdigit(*str))
            return my_strtol_core(str, end, HEX);
        if(*str != '\x20')
            return 0l;
    } while (*++str);


    return 0l;
}



long my_strtol(const char *str, char **end, int base)
{

    if (*str == '\0') {
        if (end)
            *end = (char *)str;
        return 0l;
    }

    int sign = (*str == '+') - (*str == '-');
    if (sign)
        str++;


    if (!base)
        return sign ? sign * my_strtol_base_0(str, end) : my_strtol_base_0(str, end);
    if (base == HEX)
        return sign ? sign * my_strtol_base_16(str, end) : my_strtol_base_16(str, end);


    return sign ? sign * my_strtol_core(str, end, base) : my_strtol_core(str, end, base);

}