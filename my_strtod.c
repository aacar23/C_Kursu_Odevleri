#include <ctype.h>
#include <string.h>
#include <math.h>


#define is_sign(ch) ((ch) == '-' || (ch) == '+')
#define is_startup_symbol(str) ((isdigit(*str) || is_sign(*str) || *str == '.' || strncmp_case_insensitive(str, "inf", 3) || strncmp_case_insensitive(str, "nan", 3) || strncmp_case_insensitive(str, "infinite", 8)))

int strncmp_case_insensitive(const char *str1, const char *str2, size_t n)
{
    do{
        if (toupper(*str1) != toupper(*str2))
            return toupper(*str1) - toupper(*str2);
    } while (--n && toupper(*++str1) == toupper(*++str2));
    return toupper(*str1) - toupper(*str2);
}





void add_integer(int ch, double *sum, const double *multiplier)
{
    if (isdigit(ch))
        *sum = *sum * *multiplier + ch - '0';
    else if(isxdigit(ch) && *multiplier == 16.)
        *sum = *sum * *multiplier + toupper(ch) - 'A' + 10;
}





void add_rational(int ch, double *sum, double *multiplier, double base)
{
    if (isdigit(ch))
        *sum += (ch - '0') * (*multiplier /= base);
    else if(isxdigit(ch) && base == 16.)
        *sum += (toupper(ch) - 'A' + 10) * (*multiplier /= base);
}





double *adding_while_iterating_rational(const char *start, const char *last, char **end, double *sum, int *flag, int (*std_test_func)(int ch), double base)
{
    double multiplier = 1.;
    if (start > last) {
        if (end)
            *end = (char *)start;
        return sum;
    }
    if (*flag == 1)
        return sum;
    do{
        if (!(*std_test_func)(*start)) {
            *flag = 1;
            if (end)
                *end = (char *)start;
            return sum;
        }
        add_rational(*start, sum, &multiplier, base);
    } while (++start <= last);



    if (end)
        *end = (char *)start;
    return sum;
}





double *adding_while_iterating_integer(const char *start, const char *last, char **end, double *sum, int *flag,  int (*std_test_func)(int ch), double multiplier)
{
    if (start > last)
        return sum;
    if (*flag == 1)
        return sum;



    do{
        if (!(*std_test_func)(*start)) {
            *flag = 1;
            if (end)
                *end = (char *)start;
            return sum;
        }
        add_integer(*start, sum, &multiplier);
    } while (++start <= last);



    if (end)
        *end = (char *)start;
    return sum;
}





double exponent(const char *e, char **end, double *sum, int *flag, int (*std_test_func)(int ch), int multiplier)
{
    if (*flag == 1)
        return *sum;
    e++;
    if((*e != '-' && *e != '+') && !isdigit(*e)){
        if (end)
            *end = (char *)--e;
        return *sum;
    }
    if(!(*e != '-' && *e != '+') && !strpbrk(e, "1234567890")){
        if (end)
            *end = (char *)--e;
        return *sum;
    }
    int sign = (*e == '+') - (*e == '-');
    if (sign)
        e++;
    double power = 0.;



    adding_while_iterating_integer(e, e + strlen(e) - 1, end, &power, flag, std_test_func, 10.);



    return sign ? (*sum *= pow(multiplier, sign * power)) : (*sum *= pow(multiplier, power));
}





double str_is_dot(const char *dot, char **end, double *sum)
{
    const char *e = strpbrk(dot, "Ee");
    int flag = 0;



    if (e)
        return exponent(e, end, adding_while_iterating_rational(dot + 1, e - 1, end, sum, &flag, &isdigit, 10), &flag, &isdigit, 10);

    return *adding_while_iterating_rational(dot + 1, dot + strlen(dot), end, sum, &flag, &isdigit, 10);
}





double str_is_digit(const char *first_digit, char **end, double *sum)
{
    const char *dot = strchr(first_digit, '.');
    const char *e = strpbrk(first_digit, "eE");
    int flag = 0;



    if (dot){
        if (e && e > dot)
            return exponent(e, end, adding_while_iterating_rational(dot + 1, e - 1, end, adding_while_iterating_integer(first_digit, dot - 1, end, sum, &flag, &isdigit, 10), &flag, &isdigit, 10), &flag, &isdigit, 10);

        if (e)
            return exponent(e, end, adding_while_iterating_integer(first_digit, e - 1, end, sum, &flag, &isdigit, 10), &flag, &isdigit, 10);

        return *adding_while_iterating_rational(dot + 1, dot + strlen(dot) - 1, end, adding_while_iterating_integer(first_digit, dot - 1, end, sum, &flag, &isdigit, 10), &flag, &isdigit, 10);
    }
    else{
        if (e)
            return exponent(e, end, adding_while_iterating_integer(first_digit, e - 1, end, sum, &flag, &isdigit, 10), &flag, &isdigit, 10);

        return *adding_while_iterating_integer(first_digit, first_digit + strlen(first_digit) - 1, end, sum, &flag, &isdigit, 10);
    }

}





double str_is_x(const char *point_x, char **end, double *sum)
{
    point_x++;
    do{
        if (*point_x != 0)
            break;
    } while (++point_x);


    const char *dot = strchr(point_x, '.');
    const char *p = strpbrk(point_x, "pP");
    int flag = 0;



    if (dot){
        if (p && p > dot)
            return exponent(p, end, adding_while_iterating_rational(dot + 1, p - 1, end, adding_while_iterating_integer(point_x, dot - 1, end, sum, &flag, &isxdigit, 16), &flag, &isxdigit, 16), &flag, &isdigit, 2);

        if (p)
            return exponent(p, end, adding_while_iterating_integer(point_x, p - 1, end, sum, &flag, &isxdigit, 16), &flag, &isdigit, 2);

        return *adding_while_iterating_rational(dot + 1, dot + strlen(dot) - 1, end, adding_while_iterating_integer(point_x, dot - 1, end, sum, &flag,  &isxdigit, 16), &flag, &isxdigit, 16);
    }
    if (p)
        return exponent(p, end, adding_while_iterating_integer(point_x, p - 1, end, sum, &flag,  &isxdigit, 16), &flag, &isdigit, 2);

    return *adding_while_iterating_integer(point_x, point_x + strlen(point_x) - 1, end, sum, &flag,  &isxdigit, 16);
}





double my_strtod(const char *str, char **end)
{
    double sum = 0;

    const char *start = str;

    if (!*str){
        if (end)
            *end = (char *)str;
        return sum;
    }



    do {


        if (*str != '\x20' && is_startup_symbol(str))
            break;

        if (!is_startup_symbol(str) && *str != '\x20') {
            if (end)
                *end = (char *)start;
            return sum;
        }
    } while (*++str);



    int sign = (*str == '+') - (*str == '-');
    if (sign)
        str++;



    if (*str == '0'){
        int zero_count = 0;
        while (zero_count++, !*++str)
            ;
        if (toupper(*str) == 'X' && zero_count > 1)
            return sum;
    }



    if (toupper(*str) == 'X')
        return sign ? (sign * str_is_x(str, end, &sum)) : str_is_x(str, end, &sum);
    if (isdigit(*str))
        return sign ? (sign * str_is_digit(str, end, &sum)) : str_is_digit(str, end, &sum);
    if (*str == '.')
        return sign ? (sign * str_is_dot(str, end, &sum)) : str_is_digit(str, end, &sum);



    if (end) {
        if (!strncmp_case_insensitive(str, "INFINITY", 8)) {
            *end = (char *) (str + 8);
            return INFINITY;
        }
        if (!strncmp_case_insensitive(str, "INF", 3)) {
            *end = (char *) (str + 3);
            return INFINITY;
        }
        if (!strncmp_case_insensitive(str, "NAN", 3)) {
            *end = (char *) (str + 3);
            return NAN;
        }
    }
    if (!strncmp_case_insensitive(str, "INFINITY", 8))
        return INFINITY;
    if (!strncmp_case_insensitive(str, "INF", 3))
        return INFINITY;
    if (!strncmp_case_insensitive(str, "NAN", 3))
        return NAN;



    if (end)
        *end = (char *)str;
    return sum;

}