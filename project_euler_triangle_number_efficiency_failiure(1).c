76576500#include <stdio.h>
long long nth_triangle_number(int n){
    long long triangle_number=0;
    for(int i=1;i<=n;i++){
        triangle_number+=i;
    }
    return triangle_number;
}
int is_prime(long long num){
    if(num<0){
        return 0;
    }
    else if(num==0 || num==1){
        return 0;
    }
    else if(num==2){
        return 1;
    }
    else if(num%2==0){
        return 0;
    }
    for(long long i=3;i<num;i+=2){
        if(num%i==0){
            return 0;
        }
    }
    return 1;
}
int number_of_divisors(long long num){
    int divide=2;
    int mult_temp=1;
    int mult=1;
    while(1){
        if(num==1){
            mult*=mult_temp;
            break;
        }
        back:
        if(num%divide!=0){
            mult*=mult_temp;
            mult_temp=1;
            if(divide==2){
                divide=3;
                goto back;
            }
            else{
                behind:
                divide+=2;
                if(!is_prime(divide)){
                    goto behind;
                }
                else if(num!=1 && num%divide!=0){
                    goto back;
                }
                else{
                    goto out;
                }
            }
        }
        out:
        num/=divide;
        mult_temp++;
    }
    return mult;
}
int main(void){
    int i=1;
    while(1){

        if(number_of_divisors(nth_triangle_number(i))>500){
            printf("%lld", nth_triangle_number(i));
            break;
        }i++;
    }

}