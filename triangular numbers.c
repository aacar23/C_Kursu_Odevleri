#include <stdio.h>#include <stdio.h>
long long number_of_divisors_of_a_number(long long num){
    long long count=0;
    for(int i=1;i<=num;i++){
        if(num%i==0){
            count++;
        }
    }
    return count;
}
int isprime(long long number);
long long number_divisors(int num){
    int multi=2;
    int count_temp=1;
    int count=1;
    do{
        if(num==0){
            break;
        }
        if(num%multi!=0){
            goto back;
            back:
            {
                if (multi == 2) {
                    count*=count_temp;
                    count_temp=1;
                    multi = 3;
                    if(num%multi!=0){
                        goto back;
                    }
                }
                else {
                    count*=count_temp;
                    count_temp=1;
                    multi += 2;
                    if(!isprime(multi) || num%multi!=0){
                        goto back;
                    }
                }
            }
        }
        else{
            num/=multi;
            count_temp++;
            if(num==1){
                count*=count_temp;
            }
        }
    }
    while (num!=1);
    return count;

}
int isprime(long long number){
    if(number==1 || number==0){
        return 0;
    }
    if(number==2 ||number==3||number==5||number==7){
        return 1;
    }
    else if(number%2==0 || number%3==0 ||number%5==0 ||number%7==0){
        return 0;
    }
    for(int i=11;i<number;i+=2){
        if(number%i==0){
            return 0;
        }
    }
    return 1;
}

int main(void){
    int i=0;
    while(++i){
        if(number_of_divisors_of_a_number(i*i+i)>1000){
            printf("%d",i*i+i);
            break;
        }
    }
}