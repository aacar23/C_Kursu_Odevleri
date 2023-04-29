#include <limits.h>
#include <stdio.h>
#define asize(a) (sizeof(a) / sizeof(*a))



int min_value(const int *arr, size_t size)
{
    int min = INT_MAX;
    while (size--)
        if (*(arr + size) < min)
            min = *(arr + size);
    return min;
}

int max_value(const int *arr, size_t size)
{
    int max = INT_MIN;
    while (size--)
        if (*(arr + size) > max)
            max = *(arr + size);
    return max;
}

int is_consecutive(const int *arr, size_t size)
{
    int max = max_value(arr, size);
    int min = min_value(arr, size);
    int counts[100] = {0};
    while (size--)
        counts[*(arr + size)]++;
    while (min <= max)
        if (*(counts + min++) == 0)
            return 0;
    return 1;
}

int main(void)
{
    int arr[] = {43, 44, 48, 40, 50, 47, 45, 42, 52, 49, 54, 46, 51, 41, 53};
    if (is_consecutive(arr, asize(arr)))
        printf("evet");
    else
        printf("hayir");
}