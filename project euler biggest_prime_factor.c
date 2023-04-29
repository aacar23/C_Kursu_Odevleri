#include <stdio.h>

int is_prime(long long num){
    long long count=0;
    for(int i=1;i<=num;i++){
        if(num%i==0){
            count++;
        }
    }
    if(count==2){
        return 1;
    }
    return 0;
}

long long biggest_prime_factor(long long num){
    if(num==1){
        return -1;
    }
    long long div=2;
    while(num!=1){
        if(num%div){
            if(div==2){
                div=3;
                if(num%div){
                    goto back;
                }
            }
            else{
                back:
                div+=2;
                if(!is_prime(div) || (num%div)){
                    goto back;
                }
            }
        }
        num/=div;
    }
    return div;
}

int main(void){
    printf("%lld", biggest_prime_factor(600851475143));
}
