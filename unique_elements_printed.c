#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define  SIZE 20

int icmp(const void *a, const void *b)
{
    return *(const int *)a > *(const int *)b ? -1 :
    *(const int *)a < *(const int *)b ? 1 : 0;
}

void print_array(const int *arr, size_t size)
{
    while (size--)
        printf("%d ",*arr++);
    putchar('\n');
}

void print_unique(int *arr, size_t size)
{
    size_t old_size = size;
    qsort(arr, size, sizeof(int), icmp);
    print_array(arr, SIZE);
    --size;

    if (*(arr) != *(arr + 1))
        printf("%d ", *arr);

    while (size-- - 1) {
        if (!(*(arr + size) == *(arr + size - 1) || *(arr + size + 1) == *(arr + size)))
            printf("%d ", *(arr + size));
    }

    if (*(arr + old_size - 1) != *(arr + old_size - 2))
        printf("%d", *(arr + old_size - 1));
    putchar('\n');
}



int main()
{
    int a[SIZE];

   srand((unsigned)time(NULL));

    for (int i = 0; i < SIZE; ++i) {
        a[i] = rand() % SIZE;
        printf("%d ", a[i]);
    }

    printf("\n");

    print_unique(a, SIZE);
}