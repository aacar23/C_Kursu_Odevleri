#include <math.h>
#include <string.h>

#define LOWER_CASE 0
#define UPPER_CASE 1

#define OCTAL 8
#define HEX 16
#define BINARY 2
#define DECIMAL 10

#define PREFIX 1
#define NO_PREFIX 0

char num_characters[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int digit_count(long num, int base)
{
    int count = 0;
    do{
        count++;
    } while (num /= base);
    return count;
}

char *itoa_basic(char *dest, long num, int base)
{
    int digit_cnt = digit_count(num, base);
    long divider;
    do{
        *dest++ = num_characters[num / (divider = (long)pow(base, --digit_cnt))];
        num %= divider;
    } while (digit_cnt);
    *dest = '\0';
    return dest;
}

char *itoa_with_prefixes(char *dest, long num, int base, int prefix_case)
{
    if (base == OCTAL) {
        *dest++ = '0';
        return itoa_basic(dest, num, base);
    }
    if (base == HEX){
        if (prefix_case == LOWER_CASE){
            *dest++ = '0', *dest++ = 'x';
        }
        else if(prefix_case == UPPER_CASE){
            *dest++ = '0', *dest++ = 'X';
        }
        return itoa_basic(dest, num, base);
    }

    if (base == BINARY){
        if (prefix_case == LOWER_CASE){
            *dest++ = '0', *dest++ = 'b';
        }
        else if(prefix_case == UPPER_CASE){
            *dest++ = '0', *dest++ = 'B';
        }
        return itoa_basic(dest, num, base);
    }

    return itoa_basic(dest, num, base);
}



char *itoa(char *dest, long num, int base, int has_prefix, int prefix_case, const char *postfix)
{
    if (has_prefix)
        itoa_with_prefixes(dest, num, base, prefix_case);
    else
        itoa_basic(dest, num, base);

    if(postfix)
        strcat(dest, postfix);
    return dest;
}