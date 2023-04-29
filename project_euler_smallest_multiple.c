#include <stdio.h>

int is_divisible_with_all_numbers_till(long long number,long long limit){
    for(int i=1;i<=limit;i++){
        if(number%i){
            return 0;
        }
    }
    return 1;
}

long long the_smallest_number_that_is_divisible_with_all_numbers_till_20(){
    for(long long i=2520;;i+=2){
        if(is_divisible_with_all_numbers_till(i,20))
            return i;
    }
}

int main(void){
    printf("%lld",the_smallest_number_that_is_divisible_with_all_numbers_till_20());
}