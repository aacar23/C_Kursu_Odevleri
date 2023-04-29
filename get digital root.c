#include <stdio.h>

int sum_of_digits(int num){
    int sum=0;
    while(num){
        sum+=num%10;
        num/=10;
    }
    return sum;
}
int number_of_digits(int num){
    if(num==0){
        return 1;
    }
    int count=0;
    while(num){
        num/=10;
        count++;
    }
    return count;
}
int get_digital_root(int val){
    while(number_of_digits(val)!=1){
       val= sum_of_digits(val);
    }
    return val;
}
int main(void){
    printf("%d", get_digital_root(34879));
}