#include <stdio.h>
int factorial_of(int num){
    int result=1;
    while(num){
        result*=num--;
    }
    return result;
}
int is_factorion(int num){
    if(num==0){
        return 0;
    }
    int num_copy=num;
    int sum=0;
    while(num){
        sum+= factorial_of(num%10);
        num/=10;
    }
    return num_copy==sum?1:0;
}
void test_function(int num){
    if(is_factorion(num)){
        printf("%d is a factorion number",num);
    }
    else{
        printf("%d isn't a factorion number",num);
    }
}
int main(void){
    for(int i=0,count=0;count<4&&i<100000;i++){
        if(is_factorion(i)){
            printf("%d\n",i);
            count++;
        }
    }
}