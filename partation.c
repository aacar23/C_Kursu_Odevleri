#include <stdio.h>

#define     SIZE  100

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void part(int *arr, size_t size)
{
    int *start = arr;
    int *end = arr + (int)size - 1;
    while (start <= end){
        if (*start % 2 == 0 && *end % 2 != 0)
            swap(start++, end--);
        else if(*start % 2 == 0 && *end % 2 == 0)
            swap(start, end--);
        else if(*start % 2 != 0 && *end % 2 != 0)
            swap(start++, end);
        else{
            start++;
            end--;
        }
    }
}

int main(void)
{
    int a[SIZE] = {
            1, 320, 552,   3, 989, 899, 604, 291, 279, 513, 800, 137, 857, 908,  71, 929, 272,  10, 643, 674,
            972,  58, 111, 430, 806, 834, 991, 351, 970, 212, 724, 840, 357, 147, 116, 514, 824, 865, 753, 702,
            334, 874, 176, 811, 250, 526, 214,  48, 757, 810, 438, 428, 359,  81,  38, 812, 891, 434, 595, 509,
            176, 530, 665, 179, 188, 739, 272, 513, 492,  68, 211, 490, 810, 171, 682, 983, 343, 560, 179,  89,
            761, 956, 717, 546, 350, 811, 197,  47, 905, 693, 789, 497,  20, 387,  81, 501, 223, 104, 955, 688, };
    
    part(a, SIZE);

    for (int i = 0; i < SIZE; ++i) {
        if (i && i % 20 == 0)
            printf("\n");
        printf("%3d ", a[i]);
    }
}