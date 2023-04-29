#include <stdio.h>
int is_prime(int num){
    if(num==0 || num==1){
        return 0;
    }
    else if(num==2){
        return 1;
    }
    for(int i=2;i<num;i++){
        if(num%i==0){
            return 0;
        }
    }
    return 1;
}
int sum_of_prime_divisors(int num){
    int div=2;
    int sum=0;
    if(num==0){
        return 0;
    }
    while(num!=1){
        if(num%div!=0){
            if(num==1){
                break;
            }
            this:
            {
                if (div == 2) {
                    div = 3;
                    if (num % div != 0) {
                        goto this;
                    }
                }
                else {
                    back:
                    {
                        div += 2;
                        if (!is_prime(div) || num % div != 0) {
                            goto back;
                        }
                    }
                }
            }
        }
        num/=div;
        if(div>10){
            int div_copy=div;
            while(div_copy){
                sum+=div_copy%10;
                div_copy/=10;
            }
        }
        else{
            sum+=div;
        }


    }
    return sum;
}
int sum_of_digits(int num){
    int sum=0;
    while(num){
        sum+=num%10;
        num/=10;
    }
    return sum;
}
int is_smith(int num){
    if (sum_of_prime_divisors(num)== sum_of_digits(num)){
        return 1;
    }
    return 0;
}
void test_function(int num){

}
int main(void)
{
    for(int i=0;i<=10000;i++){
        if(is_smith(i)){
            printf("%d\n",i);
        }
    }
}