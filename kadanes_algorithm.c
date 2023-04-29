#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define randomize() srand((unsigned int)time(NULL))
#define asize(a) (sizeof(a) / sizeof(*a))
int a[] = {-258, 225, -350, 323, 6, 829, 804, 732, -346, 289,
           -793, -588, 665, -681, 154, 274, -43, 877, -977, -23,
           530, 385, -514, 154, -373, 62, 790, -174, 184, 375,
           -171, 519, -354, -237, 482, -697, 717, -532, -752, 217,
           -89, -908, -382, 617, -122, 584, 617, -664, -566, 18,
           138, -496, -552, 829, 191, -478, -48, -122, 440, -686,
           256, 372, -987, 36, -872, 171, -953, 500, -603, 613,
           311, -267, -616, -384, -574, -771, -482, -881, -747, 356,
           584, 33, -135, -717, -326, 530, -328, -767, -50, 846,
           894, -499, 48, -265, -327, 574, 670, -642, -932, 84,
};


void max_subarray(const int *arr, size_t size, int *start, int *end, int *sum)
{
    int p = 0;
    int temp_sum = 0;
    int temp_start = 0;
    *start = 0;
    *end = 0;
    *sum = 0;
    for (int i = 0;i < (int)size;i++)
        if (*(arr + i) >= 0) {
            *start = i;
            break;
        }
    while (p < (int)size){
        temp_sum += *(arr + p);

        if (temp_sum < 0) {
            temp_sum = 0;
            if (*(arr + p + 1) > 0)
                temp_start = p + 1;
        }
        else if (temp_sum >= *sum) {
            *start = temp_start;
            *sum = temp_sum;
            *end = p;
        }
        p++;
    }
}

void print_array(const int *arr, size_t size)
{
    while (size--)
        printf("%d ", *arr++);
    putchar('\n');
}

void print_array_ranged(const int *start, const int *end)
{
    while (start <= end)
        printf("%d ",*start++);
    putchar('\n');
}



int main(void)
{
    randomize();
    int start;
    int end;
    int sum;
    print_array(a, asize(a));
    max_subarray(a, asize(a), &start, &end, &sum);
    print_array_ranged(a + start, a + end);
    printf("%d %d %d", start, end, sum);
}