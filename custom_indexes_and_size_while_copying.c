#include <stdio.h>

#define asize(a) (sizeof(a) / sizeof(*a))

void copy_array(const int *array, int *dest, size_t send_size)
{
    while (send_size--){
        *dest++ = *array++;
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

    printf("sending data start index: ");
    int idx_array;
    (void)scanf("%d", &idx_array);
    int idx_dest;
    printf("receiving data start index: ");
    (void)scanf("%d", &idx_dest);
    printf("how many elements to send: ");
    size_t elements;
    (void)scanf("%zu", &elements);

    copy_array(array_a + idx_array, array_b + idx_dest, elements);
    print_array(array_b, asize(array_b));
}