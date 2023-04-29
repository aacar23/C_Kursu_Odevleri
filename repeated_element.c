#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define   SIZE      100

#define sum_of_consecutive_set(arr, size) ((max_value((arr), (size)) + min_value((arr), (size)) * ((int)size)) / 2)

int max_value(const int *arr, size_t size)
{
    int max = INT_MIN;
    while (size--)
        if (*(arr + size) > max)
            max = *(arr + size);
    return max;
}

int min_value(const int *arr, size_t size)
{
    int min = INT_MAX;
    while (size--)
        if (*(arr + size) < min)
            min = *(arr + size);
    return min;
}

int sum_of_array_elements(const int *arr, size_t size)
{
    int sum = 0;
    while (size--)
        sum += *(arr + size);
    return sum;
}

int repeated_element(const int *arr, size_t size)
{
    return sum_of_array_elements(arr, size) % sum_of_consecutive_set(arr, size);
}



int main(void)
{
    int a[SIZE];

    srand((unsigned)time(NULL));
    int val = rand() % (SIZE - 1) + 1;
    a[0] = val;

    for (int i = 1; i < SIZE; ++i) {
        a[i] = i;
    }

    for (int i = 0; i < 5 * SIZE; ++i) {
        int idx1 = rand() % SIZE;
        int idx2 = rand() % SIZE;
        if (idx1 != idx2) {
            int temp = a[idx1];
            a[idx1] = a[idx2];
            a[idx2] = temp;
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        if (i % 20 == 0)
            printf("\n");
        printf("%3d ", a[i]);
    }

    printf("\ntekrar eden sayi : %d\n", val);

    printf("%d", repeated_element(a, SIZE));

}