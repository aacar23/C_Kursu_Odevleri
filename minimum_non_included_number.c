#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define   SIZE      100

int icmp(const void *vp1, const void *vp2)
{
    return *(const int *)vp1 > *(const int *)vp2 ? 1  :
           *(const int *)vp1 < *(const int *)vp2 ? -1 : 0;
}


int minimum_non_included_number(const int *arr, size_t size)
{
    if (*arr != 0)
        return 0;
    else
        for (int i = 0;i < (int)size;i++)
            if (*(arr + i) != *(arr + i + 1) - 1)
                return *(arr + i) + 1;
    return *(arr + size - 1) + 1;
}

int main(void)
{
    int a[SIZE];

    srand((unsigned)time(NULL));


    for (int i = 0, idx = 0; idx < SIZE; ++i) {
        if (rand() % (SIZE / 4) != 0)
            a[idx++] = i;
    }

    for (int i = 0; i < SIZE; ++i) {
        if (i != 0 && i % 20 == 0)
            printf("\n");
        printf("%3d ", a[i]);
    }
    printf("\n\n");

    qsort(a, SIZE, sizeof(int), icmp);


    printf("%d", minimum_non_included_number(a, SIZE));
}