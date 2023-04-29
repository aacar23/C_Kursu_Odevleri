#include <stdio.h>
long long pow_int(long long number,long long power){
    long long ret_val=1;
    for(long long i=1;i<=power;i++){
        ret_val*=number;
    }
    return ret_val;
}
long long  sum_of_the_squares_till(int n){
    long long sum=0;
    for(int i=1;i<=n;i++){
        sum+= pow_int(i,2);
    }
    return sum;
}

long long square_of_the_sum_of_the_numbers_till(int n){
    long long sum=0;
    for(int i=1;i<=n;i++){
        sum+=i;
    }
    return pow_int(sum,2);
}

int main(void){
    printf("%lld", square_of_the_sum_of_the_numbers_till(100)-sum_of_the_squares_till(100));
}