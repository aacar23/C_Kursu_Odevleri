#include <stdio.h>
int is_amicable_pair(long long num1,long long num2){
    long long count1=0;
    for(long long i =1;i<num1;i++){
        if(num1%i==0){
            count1+=i;
        }
    }
    long long count2=0;
    for(long long i=1;i<num2;i++){
        if(num2%i==0){
            count2+=i;
        }
    }
    if(count1==num2 && count2==num1){

        return 1;
    }
    return 0;
}

int main(void){
    if(is_amicable_pair(10,5)){
        printf("this pair is amicable");
    }
    else{
        printf("this pair isn't amicable");
    }
}