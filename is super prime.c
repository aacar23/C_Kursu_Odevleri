#include <stdio.h>
int is_prime(int num){
    int count=0;
    for(int i=1;i<=num;i++){
        if(num%i==0){
            count++;
        }
    }
    if(count==2){
        return 1;
    }
    return 0;
}
int is_superprime(int val){
    int count=0;
    if(!is_prime(val)){
        return 0;
    }
    for(int i=2;i<=val;i++){
        if(is_prime(i)){
            count++;
        }
    }
    if(is_prime(count)){
        return 1;
    }
    return 0;
}

void test_func(int num){
    if(is_superprime(num)){
        printf("%d is super prime\n",num);
    }
    else{
        printf("%d isn't super prime\n",num);
    }
}

int main(void){
    int test_list[]={3, 5, 11, 17, 31, 41, 59, 67, 83, 109, 127, 157, 179, 191, 211, 241, 277,
                   283, 331, 353, 367, 401, 431, 461, 509, 547, 563, 587, 599, 617, 709, 739,
                   773, 797, 859, 877, 919, 967, 991};

    for(int i=0;i<sizeof(test_list)/sizeof(test_list[1]);i++){
        test_func(test_list[i]);
    }
}