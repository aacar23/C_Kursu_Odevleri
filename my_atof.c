#include <ctype.h>
#include <string.h>
#include <math.h>

#define HEX (16.)
#define DEC (10.)


int strncmp_case_insensetive(const char *str1, const char *str2, size_t n)
{
    if (n == 0)
        return 0;

    for(;n - 1 && (toupper(*str1) == toupper(*str2));str1++, str2++, n--)
        ;
    return toupper(*str1) - toupper(*str2);
}



void assign_start(double *sum, double base, int ch)
{
    if (base == DEC)
        *sum = *sum * base + ch - '0';
    else if(base == HEX){
        ch = toupper(ch);
        if (isdigit(ch))
            *sum = *sum * base + ch - '0';
        else if(isxdigit(ch) && isalpha(ch))
            *sum = *sum * base + ch - 'A' + 10;
    }
}




void decimal_assign_dot(double *sum, double base, double *multiplier, int ch)
{
    if (base == DEC)
        *sum += (ch - '0') * (*multiplier /= base);
    else if(base == HEX){
        ch = toupper(ch);
        if (isdigit(ch))
            *sum += (ch - '0') * (*multiplier /= base);
        else if(isxdigit(ch) && isalpha(ch))
            *sum += (ch - 'A' + 10) * (*multiplier /= base);
    }
}





double *my_atof_between_before_point(const char *start, const char *end, double *sum, int (*std_test_func)(int), double base, int *flag)
{
    if (*flag == 1)
        return sum;

    while (start <= end){
        if ((*std_test_func)(*start))
            assign_start(sum, base, *start);
        else if(*start != '.')
            return (*flag = 1), sum;
        start++;
    }

    return sum;
}






double *my_atof_between_after_point(const char *start, const char *end, double *sum, int (*std_test_func)(int), double base, int *flag)
{
    double multiplier = 1;

    if (*flag == 1)
        return sum;

    while (start <= end){
        if ((*std_test_func)(*start))
            decimal_assign_dot(sum, base, &multiplier, *start);
        else if(toupper(*start) != 'P' && toupper(*start) != 'E')
            return (*flag = 1), sum;
        start++;
    }

    return sum;
}





double *exponent(const char *exp, const char *end, double *sum, double base, const int *flag)
{
    if (*flag == 1)
        return sum;

    if(exp > end)
        return sum;
    exp++;

    int sign = (*exp == '+') - (*exp == '-');
    if (sign)
        exp++;

    double power = 0;

    while (exp <= end) {
        if (!isdigit(*exp)){
            if (sign)
                (*sum *= pow(base, sign * power));
            else
                (*sum *= pow(base, power));
            return sum;
        }
        power = power * 10. + *exp++ - '0';
    }

    if (sign)
        (*sum *= pow(base, sign * power));
    else
        (*sum *= pow(base, power));

    return sum;
}





double my_atof_str_is_x(const char *str, double *sum, int *flag)
{
    const char *end = str + strlen(str) - 1;
    const char *dot = strchr(str, '.');
    const char *p = strpbrk(str, "pP");

    if (dot){
        if (p > dot)
            return *exponent(p, end, my_atof_between_after_point(dot + 1, p - 1, my_atof_between_before_point(str + 1,dot - 1, sum, &isxdigit, HEX, flag), &isxdigit, HEX, flag), 2, flag);
        if(p)
            return *exponent(p, end, my_atof_between_before_point(str + 1, p - 1, sum, &isxdigit, HEX, flag), 2, flag);

        return *my_atof_between_after_point(dot + 1, end, my_atof_between_before_point(str + 1, dot - 1, sum, &isxdigit, HEX, flag), &isxdigit, HEX, flag);
    }

    if (p)
        return *exponent(p, end, my_atof_between_before_point(str + 1, p - 1, sum, &isxdigit, HEX, flag), 2, flag);

    return *my_atof_between_before_point(str + 1, end, sum, &isxdigit, HEX, flag);


}






double my_atof_str_is_dot(const char *str, double *sum, int *flag)
{
    const char *end = str + strlen(str) - 1;
    const char *e = strpbrk(str, "eE");

    if (e)
        return *exponent(e, end, my_atof_between_after_point(str + 1, e - 1, sum, &isdigit, DEC, flag), DEC, flag);

    return *my_atof_between_after_point(str + 1, end, sum, &isdigit, DEC, flag);
}






double my_atof_str_is_digit(const char *str, double *sum, int *flag)
{
    const char *end = str + strlen(str) - 1;
    const char *dot = strchr(str, '.');
    const char *e = strpbrk(str, "eE");

    if (e && (((e < dot) || !dot)))
        return *exponent(e, end, my_atof_between_before_point(str, e - 1, sum, &isdigit, DEC, flag), DEC, flag);

    if (dot)
        return my_atof_str_is_dot(dot, my_atof_between_before_point(str, dot - 1, sum, &isdigit, DEC, flag), flag);

    return *my_atof_between_before_point(str, end, sum, &isdigit, DEC, flag);
}






double my_atof(const char *str)
{
    double sum = 0;

    do{
        if (!isspace(*str))
            break;
    } while (*++str);

    int sign = (*str == '+') - (*str == '-');
    if (sign)
        str++;

    if (*str == '0') {
        int zero_count = 0;
        while (zero_count++, *++str == '0')
            ;
        if (toupper(*str) == 'X' && zero_count > 1)
            return sign ? sign * sum : sum;
    }

    int flag = 0;

    if (toupper(*str) == 'X')
        return sign ? sign * my_atof_str_is_x(str, &sum, &flag) : my_atof_str_is_x(str, &sum, &flag);
    if (*str == '.')
        return sign ? sign * my_atof_str_is_dot(str, &sum, &flag) : my_atof_str_is_dot(str, &sum, &flag);
    if (isdigit(*str))
        return sign ? sign * my_atof_str_is_digit(str, &sum, &flag) : my_atof_str_is_digit(str, &sum, &flag);
    if (!strncmp_case_insensetive(str, "INF", 3))
        return INFINITY;
    if (!strncmp_case_insensetive(str, "NAN", 3))
        return NAN;

    return 0.;

}