#include <stdio.h>

int number_of_digits(long long num){
    int count=0;
    while(num){
        num/=10;
        count++;
    }
    return count;
}
int has_2_3_digited_factors(long long num){

    for(long long i=100;i<=999;i++){
        if(num%i==0 && number_of_digits(num/i)==3){
            return 1;
        }
    }
    return 0;
}
long long pow_int(long long num,long long power){
    if(power==0){
        return 1;
    }
    long long num_copy=num;
    for(int i=1;i<power;i++){
        num_copy*=num;
    }
    return num_copy;
}
long long reverse_number(long long num){
    long long reversed_number=0;
    int digit=number_of_digits(num);
    while(digit){

        reversed_number+=num%10* pow_int(10,--digit);
        num/=10;
    }
    return reversed_number;
}
int is_palindrome(long long num){
    if(reverse_number(num)==num){
        return 1;
    }
    return 0;
}

int main(void){
    long long biggest=0;
    for(long long i=10201;i<999*999;i++){
        if(is_palindrome(i) && has_2_3_digited_factors(i)){
            biggest=i;
        }
    }
    printf("%lld",biggest);
}