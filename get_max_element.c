#define RAND_LINUX
#include <stdio.h>


#if defined RAND_LINUX
#define set_random_array set_random_array_linux
#else
#include <stdlib.h>
#include <time.h>
#define randomize() srand(time(NULL));
#define set_random_array set_random_array_standard
#endif


void set_random_array_linux(int *array, size_t size, int less)
{
    int element;
    FILE *f = fopen("/dev/urandom", "r");
    while(size--){
        fread(&element, sizeof(element), 1, f);
        *array++ = element % less;
    }
    fclose(f);
}

void set_random_array_standard(int *array, size_t size, int less)
{
    while(size--){
        *array++ = rand() % less;
    }
}

void print_array(const int *array, size_t size)
{
    for(unsigned int i = 0;i < size;i++){
        printf("%d ", array[i]);
    }
    putchar('\xA');
}

int get_array_max(const int *array, size_t size)
{
    int max=*array;
    for(unsigned int i = 0;i < size;i++){
        if(array[i] > max){
            max = array[i];
        }
    }
    return max;
}
int main(void){
    int a[20];
    set_random_array(a, arr_size(a), 20);
    print_array(a, arr_size(a));
    printf("%d", get_array_max(a, arr_size(a)));
}