#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
long long isprime(long long num){
    if(num<=1){
        return 0;
    }
    long long divide_count=0;
    for(long long i=1;i<=num;i++){
        if(num%i==0){
            divide_count++;
        }
    }
    if(divide_count==2){
        return 1;
    }
    return 0;
}
void print_primes_till(long long num){
    for(long long i=0;i<=num;i++){
        if(isprime(i)){
            printf("%lld\xA",i);
        }
    }
}
void print_prime_divisible(long long num){
    for(long long i=0;i<=num;i++){
        if(isprime(i) && num%i==0){
            printf("%lld\xA",i);
        }
    }
}

void print_prime_divisible_classic(long long num){

    back:{
        for(long long i=0;i<=num;i++){
            if(isprime(i) && num%i==0){
                printf("%lld\xA",i);
                num/=i;
                goto back;
            }
        }
    }
}
int main(void){
    int number;
    printf("Enter a number for operations:");
    scanf("%lld",&number);
    if(isprime(number)){
        printf("Number %d is a prime number\xA",number);
    }
    else{
        printf("Number %d is not a prime number\xA",number);
    }
    print_prime_divisible_classic(number);
}