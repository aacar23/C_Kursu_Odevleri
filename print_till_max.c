#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define asize(array) (sizeof(a) / sizeof(*a))
#define randomize() srand(time(NULL))



int* max_element_of_array(const int *array_ptr, size_t size)
{
    int *max = (int *)array_ptr;
    while (size--) {
        if (*array_ptr > *max)
            max = (int *) array_ptr;
        array_ptr++;
    }
    return max;
}

void set_array_random(int *array_ptr, size_t size, int less)
{
    while (size--){
        *array_ptr++ = rand() % 2 ? rand() % less * -1 : rand() % less;
    }
}


void print_array(const int *array_ptr, size_t size)
{
    while(size--)
        printf("%d ", *array_ptr++);
    putchar('\n');
}



int main(void)
{
    int a[20];
    randomize();
    set_array_random(a, asize(a), 20);
    print_array(a, asize(a));
    size_t size_ptr = (size_t)(max_element_of_array(a, asize(a)) - a);
    print_array(a, size_ptr + 1);

}