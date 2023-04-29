#include <stdbool.h>
long long reverse_the_number(int x)
{
    long long ret = 0;
    while (x){
        ret *= 10;
        ret += x % 10;
        x /= 10;
    }
    return ret;
}

bool isPalindrome(int x){
    if (x >= 0 && (long long)x == reverse_the_number(x))
        return true;
    return false;    
}