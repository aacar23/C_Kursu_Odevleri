#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define malloc(bytes) (checked_malloc(bytes))
#define randomize() srand((unsigned)(time(NULL)))

#define ROWS 100
#define COLUMNS 20

void *checked_malloc(size_t bytes)
{
    void *new_block = (malloc)(bytes);
    if (!new_block){
        fprintf(stderr, "cannot allocate memory");
        exit(1);
    }
    return new_block;
}

int *contiguous_matrix_allocation(size_t rows, size_t columns)
{
    int *new_matrix = (int *)malloc(rows * columns * sizeof(int));
    return new_matrix;
}

void set_array_random_linux(int *arr, int mod, size_t number_of_elements)
{
    FILE *f = fopen("/dev/urandom", "r");
    while (number_of_elements--){
        int element;
        fread(&element, sizeof(element), 1, f);
        *arr++ = element % mod;
    }
    fclose(f);
}

void set_array_random_standard(int *arr, int mod, size_t number_of_elements)
{
    while (number_of_elements--)
        *arr++ = rand() % 2 ? rand() % mod : -rand() % mod;
}


int *contiguous_matrix_allocation_with_preassigned_random_values(int mod, size_t rows, size_t columns, void (*setter_func)(int *arr, int mod, size_t number_of_elements))
{
    int *new_matrix = contiguous_matrix_allocation(rows, columns);
    (*setter_func)(new_matrix, mod, rows * columns);
    return new_matrix;
}


void print_contiguously_allocated_matrix(int *contiguously_allocated_matrix, size_t rows, size_t columns)
{
    while (rows--){
        for (size_t i = 0;i < columns;i++)
            printf("%d,", *contiguously_allocated_matrix++);
        putchar('\n');
    }
}