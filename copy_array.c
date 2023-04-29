#include <stdio.h>

#define asize(a) (sizeof(a) / sizeof(*a))

void copy_array(const int *array, int *dest, size_t array_size, size_t dest_size)
{
    if (array_size <= dest_size){
       while (array_size--){
           *dest++ = *array++;
       }
    }
    else{
        while (dest_size--){
            *dest++ = *array++;
        }
    }
}

void set_array_random(int *array, size_t size)
{
    int element;
    FILE *f = fopen("/dev/urandom", "r");
    while(size--){
        fread(&element, sizeof(element), 1, f);
        *array++ = element;
    }
    fclose(f);
}

void print_array(const int *array, size_t size)
{
    while (size--){
        printf("%d ", *array++);
    }
    putchar('\n');
}

int main(void)
{
    int array_a[15] = {0};
    int array_b[12] = {0};
    set_array_random(array_a, asize(array_a));
    print_array(array_a, asize(array_a));
    copy_array(array_a, array_b, asize(array_a), asize(array_b));
    print_array(array_b, asize(array_b));
}