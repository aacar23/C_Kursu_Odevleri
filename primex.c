#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define randomize() srand(time(NULL));
#define LIMIT 10000
int number_of_digits(int num)
{
    int digits = 0;
    while (num > 0){
        num /= 10;
        digits++;
    }
    return digits;
}

int sum_of_digits(int num)
{
    int sum = 0;
    while (num > 0){
        sum += num%10;
        num /= 10;
    }
    return sum;
}

int is_prime(int num)
{
    if(num<2){
        return 0;
    }

    if (!(num % 2)){
        return num == 2;
    }

    if(!(num % 3)){
        return num == 3;
    }

    if(!(num % 5)){
        return num == 5;
    }

    for(int i = 7;i * i < num;i += 2){
        if(!(num % i)){
            return 0;
        }
    }

    return 1;
}


int is_primex(int num){
    do {
        if (!is_prime(num)){
            return 0;
        }
        num=sum_of_digits(num);
    }while (number_of_digits(num) != 1);
    return 1;
}

void primex_ui(int num)
{
    if (is_primex(num)){
        printf("%d is a primex number", num);
    }
    else{
        printf("%d is not a primex number", num);
    }
}


int main(void){
    randomize();
    primex_ui(rand() % LIMIT);
}