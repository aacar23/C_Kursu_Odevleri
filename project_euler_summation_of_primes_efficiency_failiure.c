#include <stdio.h>

int is_prime(long long num){
    if(num==2){
        return 1;
    }
    else if(num==3){
        return 1;
    }
    else if(num==5){
        return 1;
    }
    else if(num%2==0){
        return 0;
    }
    else if(num%3==0){
        return 0;
    }
    else if(num%5==0){
        return 0;
    }

    for(int i=7;i<num;i+=2){
        if(num%i==0){
            return 0;
        }
    }
    return 1;
}

int main(void){
    long long sum=2;
    for(int i=3;i<2000000;i+=2){
        if(is_prime(i)){
            sum+=i;
        }
    }
    printf("%lld",sum);
}