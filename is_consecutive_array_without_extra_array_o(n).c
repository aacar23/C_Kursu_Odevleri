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

int sum_of_array_elements(const int *arr, size_t size)
{
    int sum = 0;
    while (size--)
        sum += *(arr + size);
    return sum;
}

int is_consecutive(const int *arr, size_t size)
{
    return sum_of_array_elements(arr, size) == (max_value(arr, size) + min_value(arr, size)) * (int)size / 2;
}

int main(void)
{
    int arr[] = {43, 44, 48, 40, 50, 47, 45, 42, 52, 49, 54, 46, 51, 41, 53};
    if (is_consecutive(arr, asize(arr)))
        printf("evet");
    else
        printf("hayir");
}