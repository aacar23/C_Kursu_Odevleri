#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define			SIZE		20

int max_value(const int *arr, size_t size)
{
    int max = INT_MIN;
    while (size--)
        if (*(arr + size) > max)
            max = *(arr + size);
    return max;
}

void print_histogram(int *arr, size_t size)
{
    int *temp_arr = arr;
    int max = max_value(arr, size);
    size_t temp_size = size;
    while (temp_size--)
        *temp_arr++ -= max;
    for (int i = 0;i < max;i++){
        for (int k = 0;k < (int)size;k++) {
            if ((*(arr + k))++ < 0)
                printf("       ");
            else
                printf("*      ");
        }
        putchar('\n');
    }
}

int main(void)
{
    int a[SIZE];

    srand((unsigned)time(0));
    for (int i = 0; i < 20; ++i) {
        a[i] = rand() % 20 + 1;
        printf("%d ", a[i]);
    }
    printf("\n");
    print_histogram(a, SIZE);
}
