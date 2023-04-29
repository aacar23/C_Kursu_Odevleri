#include <stdio.h>
#define SIZE 20
#define LESS 100
void reverse(int *dest, size_t size)
{
    for(unsigned int i = 0;i < size / 2;i++){
        int temp = dest[i];
        dest[i] = dest[size - 1 - i];
        dest[size - 1 - i] = temp;
    }
}

void set_array_random(int *array, size_t size, int less){
    int element;
    FILE *f = fopen("/dev/random", "r");
    for(unsigned int i = 0;i < size;i++){
        fread(&element, sizeof(element), 1, f);
        array[i] = element % less;
    }
    fclose(f);
}

void print_array(const int *array, size_t size){
    for(unsigned int i = 0;i < size;i++){
        printf("%d ", array[i]);
    }
    putchar('\xA');
}

int main(void){
    int arr[SIZE];
    set_array_random(arr, SIZE, LESS);
    print_array(arr, SIZE);
    reverse(arr, SIZE);
    print_array(arr, SIZE);

}