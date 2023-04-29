#include <stdio.h>
#include <math.h>
#define arr_size(a) (sizeof(a)/sizeof(*a))
void set_array_random(int *arr, size_t size, int modulus_value)
{
    int element;
    FILE *f = fopen("/dev/urandom","r");
    while(size--){
        fread(&element,sizeof(element),1,f);
        *arr++ = element % modulus_value;
    }
    fclose(f);
}

int sum_of_elements(const int *arr, size_t size)
{
    int sum = 0;

    while(size--){
        sum += *arr++;
    }

    return sum;
}

double get_mean(const int *arr, size_t size)
{
    return (double)sum_of_elements(arr, size) / size;
}

double standard_deviation(const int *arr, int size)
{
    double sum = 0;
    double mean = get_mean(arr, size);
    for(int i = 0;i < size;i++) {
        sum += ((double) (*arr) - mean) * ((double) (*arr) - mean);
        (void) (*arr++);
    }
    return sum / ((double)size - 1);

}

void print_array(const int *arr, size_t size){
    while(size--){
        printf("%d ",*arr++);
    }
    putchar('\xA');
}

int main(void)
{
    int arr[10];
    set_array_random(arr, arr_size(arr), 20);
    print_array(arr, arr_size(arr));
    printf("%d\n", sum_of_elements(arr, arr_size(arr)));
    printf("%lf\n", get_mean(arr, arr_size(arr)));
    printf("%lf\n", standard_deviation(arr, arr_size(arr)));
}