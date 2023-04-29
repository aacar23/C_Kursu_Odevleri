#include <stdio.h>


#define asize(array) (sizeof(array) / sizeof(*array))
#define end_pointer(array) ((array) + asize(array))

void reverse_copy(const int *start_send, const int *end_send, int *start_dest)
{
    while (start_send < end_send)
        *start_dest++ = *--end_send;
}

void set_array_random(int *array_start, int *array_end, int less)
{
    int element;
    FILE *f = fopen("/dev/urandom", "r");
    while (array_start != array_end){
        fread(&element, sizeof(element), 1, f);
        *array_start++ = element % less;
    }
    fclose(f);
}

void print_array(const int *array_start, const int *array_end)
{
    while (array_start < array_end){
        printf("%d ", *array_start++);
    }
    putchar('\xA');
}

int main(void)
{
    int a[20];
    int b[20];
    set_array_random(a, end_pointer(a), 20);
    print_array(a, end_pointer(a));
    reverse_copy(a, end_pointer(a), b);
    print_array(b, end_pointer(b));
}