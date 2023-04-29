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
    else if(!(num%2)){
        return 0;
    }
    else if(!(num%3)){
        return 0;
    }
    else if(!(num%5)){
        return 0;
    }
    for(int i=7;i<num;i+=2){
        if(!(num%i)){
            return 0;
        }
    }
    return 1;
}
long long get_nth_prime_number(int n){
    if(n-1==0){
        return 2;
    }
    for(int i=3,count=1;count<=n-1;i+=2){
        if(is_prime(i)){
            count++;
            if(count==n){
                return i;
            }
        }

    }
}
int main(void){
    printf("%lld", get_nth_prime_number(10001));
}