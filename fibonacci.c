#include <stdio.h>
long long fibonacci(long long n){
    long long next_copy=2;
    long long now=1;
    long long next=2;
    if(n==1 || n==2){
        return 1;
    }
    if(n==3){
        return 2;
    }
    for(long long i=1;i<=n-3;i++){
        next_copy=next;
        next+=now;
        now=next_copy;
    }
    return next;
}

int main(void){
    printf("%lld", fibonacci(1000));
}