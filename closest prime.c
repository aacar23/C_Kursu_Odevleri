#include <stdio.h>

int is_prime(int num){
    if(num==0||num==1){
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

int closest_prime(int value){
    int ret_val=0;
    for(int i=2;i<value;i++){
        if(is_prime(i)){
            ret_val=i;
        }
    }
    if(ret_val==0){
        return -1;
    }
    return ret_val;
}


int main()
{
    int a[10] = {1810, 2678, 8887, 13452, 16982, 21777, 29016, 33010, 36876, 42011};
    int b[10] = {1801, 2677, 8867, 13451, 16981, 21773, 29009, 32999, 36871, 41999};
    int k;

    for (k = 0; k < 10; ++k) {
        if (closest_prime(a[k]) != b[k]) {
            printf("yanlis cozum\n");
            return 0;
        }
    }

    printf("muhtemelen dogru cozum\n");
}