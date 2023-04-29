#include <stdio.h>
#define arr_size(arr) (sizeof(arr) / sizeof(*arr))
int sum_of_elements(const int *array, size_t size){
    int sum = 0;
    while(size--){
        sum += *array++;
    }
    return sum;
}

double get_mean(const int *array, size_t size){
    return (double)sum_of_elements(array, size) / size;
}

void print_array(const int *array, size_t size){
    while(size--){
        printf("%d ",*array++);
    }
    putchar('\012');
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
    int arr[10];
    set_array_random(arr, arr_size(arr), 20);
    print_array(arr, arr_size(arr));
    printf("%d\n", sum_of_elements(arr, arr_size(arr)));
    printf("%lf", get_mean(arr, arr_size(arr)));
}
