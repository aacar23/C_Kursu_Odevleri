#include <stdio.h>
#include <ctype.h>
long long collatz_count(long long num){
    if(num==0){
        return 0;
    }
    long long count=0;
    while(num!=1){
        if(num%2==0){
            num/=2;
            count++;
        }
        else{
            num=num*3+1;
            count++;
        }
    }
    return count;
}
long long biggest_collatz_between(long long start,long long end){
    if(start>end){
        long long temp=start;
        start=end;
        end=temp;
    }
    long long biggest=0;
    for(long long i=start;i<=end;i++){
        if(collatz_count(i)> collatz_count(biggest)){
            biggest=i;
        }
    }
    return biggest;
}
int main(void){
    printf("%lld",biggest_collatz_between(1600000,1700000));
}