#include <limits.h>

int reverse(int x){
    long long reversed = 0;
    while(x){
        reversed *= 10;
        reversed += x % 10;
        x /= 10;
    }
    if (reversed < INT_MIN || reversed > INT_MAX)
        return 0;
    return (int)reversed;
   
}