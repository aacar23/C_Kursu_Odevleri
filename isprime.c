#include <stdio.h>


long long isprime(long long num){
    if(num==1 || num==0){
        return 0;
    }
    long long divide_count=0;
    for(long long i=1;i<=num;i++){
        if(num%i==0){
            divide_count++;
        }
    }
    if(divide_count!=2){
        return 0;
    }
    else{
        return 1;
    }
}
void print_primes_till(long long num){
    for(int i=0;i<=num;i++){
        if(isprime(i)){
            printf("%d\xA",i);
        }
    }
}
