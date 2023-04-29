#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define randomize() srand((unsigned)(time(NULL)))

#define set_two_dimensional_array_std(ptr, less, rows, columns) set_two_dimensional_array_std((*(ptr)), (less), (rows), (columns))
#define set_two_dimensional_array_linux(ptr, less, rows, columns) set_two_dimensional_array_linux((*(ptr)), (less), (rows), (columns))
#define print_two_dimensional_array(ptr, rows, columns) print_two_dimensional_array((*(ptr)), (rows), (columns))
#define set_array_linux(ptr, less, size) set_array_linux((*(ptr)), (less), (size))
#define set_array_std(ptr, less, size) set_array_std((*(ptr)), (less), (size))

#define ROWS 10
#define COLUMNS 10

void (set_two_dimensional_array_std)(int *arr, int less, size_t rows, size_t columns)
{

    while (rows--){
        for (size_t i = 0; i < columns ; ++i) {
            int random_number = rand();
            *arr++ = random_number % 2 ? -random_number % less : random_number % less;
        }
    }
}

void (set_two_dimensional_array_linux)(int *arr, int less, size_t rows, size_t columns)
{
    int element;
    FILE *f = fopen("/dev/urandom", "r");
    while (rows--){
        for (size_t i = 0;i < columns ; ++i){
            fread(&element, sizeof(element), 1, f);
            *arr++ = element % less;
        }
    }
    fclose(f);
}


void (set_array_std)(int *arr, int less, size_t size)
{

    while (size--) {
        int random_number = rand();
        *arr++ = random_number % 2 ? -random_number % less : random_number % less;
    }
}

void (set_array_linux)(int *arr, int less, size_t size)
{
    int element;
    FILE *f = fopen("/dev/urandom", "r");
    while (size--){
        fread(&element, sizeof(element), 1, f);
        *arr++ = element % less;
    }
    fclose(f);
}


void (print_two_dimensional_array)(const int *arr, size_t rows, size_t columns)
{
    while (rows--) {
        for (size_t i = 0;i < columns;i++)
            printf("%-5d ", *arr++);
        putchar('\n');
    }
    putchar('\n');
}

int main(void)
{
    randomize();
    int a[ROWS][COLUMNS];
    set_two_dimensional_array_linux(a, 20, ROWS, COLUMNS);
    print_two_dimensional_array(a, ROWS, COLUMNS);
    set_two_dimensional_array_std(a, 20, ROWS, COLUMNS);
    print_two_dimensional_array(a, ROWS, COLUMNS);
    set_array_linux(a, 20, ROWS * COLUMNS);
    print_two_dimensional_array(a, ROWS, COLUMNS);
    set_array_std(a, 20, ROWS * COLUMNS);
    print_two_dimensional_array(a, ROWS, COLUMNS);
}