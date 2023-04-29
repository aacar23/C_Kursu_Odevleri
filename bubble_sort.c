#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort_array(int *array, size_t size)
{
    for(int i = 0;i < (int)size - 1;i++){
        for(int k = 0;k < (int)size - 1 - i;k++){
            if(array[k]>array[k+1]){
                swap(&array[k], &array[k+1]);
            }
        }
    }
}

void print_array(const int *array, size_t size)
{
    while(size--){
        printf("%d ", *array++);
    }
    putchar('\n');
}

void set_array_random(int *array, size_t size, int less){
    int element;
    FILE *f = fopen("/dev/urandom", "r");
    while(size--){
        fread(&element, sizeof(element), 1, f);
        *array++ = element % less;
    }
    fclose(f);
}

int main(void){
    int array[10];
    set_array_random(array, 10, 20);
    print_array(array, 10);
    bubble_sort_array(array, 10);
    print_array(array, 10);
}