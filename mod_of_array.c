#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#define randomize() srand((unsigned int)time(NULL))
#define asize(a) (sizeof(a) / sizeof(*a))
void max_array_element(const int *arr, size_t size, int *value, int *index)
{
    *value = INT_MIN;
    *index = INT_MIN;
    while (size--)
        if (*(arr + size) > *value) {
            *value = *(arr + size);
            *index = (int) size;
        }

}


int max_value(const int *arr, size_t size)
{
    int max = INT_MIN;
    while (size--)
        if (*(arr + size) > max)
            max = *(arr + size);
    return max;
}

void mod(const int *arr, size_t size, int *return_value, int *return_times)
{
    int size_of_counts = max_value(arr, size) + 1;
    int *counts = malloc(sizeof(int) * (size_of_counts));
    for (int i = 0; i < size_of_counts; ++i)
        *(counts + i) = 0;
    while (size--)
        (*(counts + *(arr + size)))++;
    max_array_element(counts, size_of_counts,return_times ,return_value);
    free(counts);
}

void set_array_random(int *arr , size_t size, int less)
{
    while (size--)
        *arr++ = rand() % less;
}

void print_array(const int *arr, size_t size)
{
    while (size--)
        printf("%d ", *arr++);
    putchar('\n');
}

int main(void) 
{
    randomize();
    int array[10] = {0};
    set_array_random(array, asize(array), 20);
    print_array(array, asize(array));
    int value;
    int times;
    mod(array, asize(array), &value, &times);
    if(times == 1)
    {
        printf("all are equally occured");
        return 0;
    }
    printf("%d is the mod and occurs %d times", value, times);
    return 0;
}