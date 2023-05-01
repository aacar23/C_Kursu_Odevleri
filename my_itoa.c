#include <math.h>
#include <string.h>
#include <ctype.h>

#define LOWER_CASE 0
#define UPPER_CASE 1

#define OCTAL 8
#define HEX 16
#define BINARY 2
#define DECIMAL 10

#define PREFIX 1
#define NO_PREFIX 0

#define SIGN 1
#define NO_SIGN 0

char num_characters[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int digit_count(long num, int base)
{
    int count = 0;
    do{
        count++;
    } while (num /= base);
    return count;
}


char *ltoa_basic_lower(char *dest, long num, int base)
{
    if (num < 0)
        num = -num;
    int digit_cnt = digit_count(num, base);
    long divider;
    do{
        *dest++ = tolower(num_characters[num / (divider = (long)pow(base, --digit_cnt))]);
        num %= divider;
    } while (digit_cnt);
    *dest = '\0';
    return dest;
}


char *ltoa_basic_upper(char *dest, long num, int base)
{
    if (num < 0)
        num = -num;
    int digit_cnt = digit_count(num, base);
    long divider;
    while (digit_cnt--){
        *dest++ = num_characters[num / (divider = (long)pow(base, digit_cnt))];
        num %= divider;
    }
    *dest = '\0';
    return dest;
}


char *ltoa_with_prefixes(char *dest, long num, int base, int prefix_case, char *(*ltoa_basic)(char *dest, long num, int base))
{
    if (base == OCTAL) {
        *dest++ = '0';
        return ltoa_basic(dest, num, base);
    }
    if (base == HEX){
        if (prefix_case == LOWER_CASE){
            *dest++ = '0', *dest++ = 'x';
        }
        else if(prefix_case == UPPER_CASE){
            *dest++ = '0', *dest++ = 'X';
        }
        return ltoa_basic(dest, num, base);
    }

    if (base == BINARY){
        if (prefix_case == LOWER_CASE){
            *dest++ = '0', *dest++ = 'b';
        }
        else if(prefix_case == UPPER_CASE){
            *dest++ = '0', *dest++ = 'B';
        }
        return ltoa_basic(dest, num, base);
    }

    return ltoa_basic(dest, num, base);
}



char *ltoa(char *dest, long num, int base, int has_prefix, int has_sign, int prefix_case, const char *postfix, int num_case)
{
    if (num > 0 && has_sign)
        *dest++ = '+';

    if (num < 0)
        *dest++ = '-';

    if (num_case == UPPER_CASE || base <= 10) {
        if (has_prefix)
            ltoa_with_prefixes(dest, num, base, prefix_case, &ltoa_basic_upper);
        else
            ltoa_basic_upper(dest, num, base);
    }
    else if (num_case == LOWER_CASE) {
        if (has_prefix)
            ltoa_with_prefixes(dest, num, base, prefix_case, &ltoa_basic_lower);
        else
            ltoa_basic_lower(dest, num, base);
    }

    if(postfix)
        strcat(dest, postfix);
    return dest;
}