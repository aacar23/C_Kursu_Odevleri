#include <stdio.h>
long long count_of_collatz_terms(long long num){
    if(num==0){
        return 0;
    }
    long long count=1;
    do{
        if(num%2!=0){
            num=num*3+1;
            count++;
        }
        else{
            num/=2;
            count++;
        }
    }
    while(num!=1);
    return count;
}
int number_that_has_most_collatz_terms_till(int n){
    int biggest=0;
    for(int i=1;i<n;i++){
        if(count_of_collatz_terms(i)> count_of_collatz_terms(biggest)){
            biggest=i;
        }
    }
    return biggest;
}
int main(void){
    printf("%d", number_that_has_most_collatz_terms_till(1000000));
}