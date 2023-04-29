#include <stdio.h>
#define asize(a) (sizeof(a) / sizeof(*a))
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void dutch_flag_algorithm(int *arr, size_t size)
{
    int *start = arr;
    int *mid = arr;
    int *end = arr + (int)size - 1;
    while (mid <= end){
        if (*mid == 0)
            swap(start++, mid++);
        else if (*mid == 1)
            mid++;
        else
            swap(end--, mid);
    }
}

void set_array_random(int *arr, size_t size, int less)
{
    int element;
    FILE *f = fopen("/dev/urandom", "r");
    while (size--){
        fread(&element, sizeof(element), 1, f);
        *arr++ = element % less;
    }
    fclose(f);
}

void print_array(const int *arr, size_t size)
{
    while (size--)
        printf("%d ", *arr++);
    putchar('\n');
}

int main(void)
{
    int a[] = {1, 2, 2, 0, 1, 0, 1, 0, 0, 1, 1, 2, 1, 0, 1, 2, 0, 0, 1, 0};
    print_array(a, asize(a));
    dutch_flag_algorithm(a, asize(a));
    print_array(a, asize(a));
}