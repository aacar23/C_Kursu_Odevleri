#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define randomize() srand((unsigned)(time(NULL)))
#define malloc(bytes) (checked_malloc(bytes))

#define ROWS 50
#define COLUMNS 50

void *checked_malloc(size_t bytes)
{
    void *new_block = (malloc)(bytes);
    if (!new_block){
        fprintf(stderr, "cannot allocate memory");
        exit(EXIT_FAILURE);
    }
    return new_block;
}


int **create_new_contiguous_matrix_that_has_usability_with_mathematical_matrix_notion(size_t rows, size_t columns)
{
    int *new_matrix = (int *)malloc(rows * columns * sizeof(int));
    int **interface =  (int **)malloc(rows * sizeof(int *));
    for (size_t i = 0;i < rows;i++)
        *(interface + i) = new_matrix + columns * i;
    return interface;
}

void set_array_random_linux(int *arr, int mod, size_t size)
{
    FILE *f = fopen("/dev/urandom", "r");
    while (size--){
        int element;
        fread(&element, sizeof(element), 1, f);
        *arr++ = element % mod;
    }
    fclose(f);
}

void set_array_random_standard(int *arr, int mod, size_t size)
{
    while (size--)
        *arr++ = rand() % 2 ? rand() % mod : -rand() % mod;
}

int **create_new_contiguous_matrix_that_has_usabilitty_wiyh_mathematical_matrix_notion_filled_with_random_values(int mod, size_t rows, size_t columns, void (*setter_func)(int *arr, int mod, size_t size))
{
    int **new_matrix = create_new_contiguous_matrix_that_has_usability_with_mathematical_matrix_notion(rows, columns);
    (*setter_func)(*new_matrix, mod, rows * columns);
    return new_matrix;
}

void print_matrix(const int * const *arr ,size_t rows, size_t columns)
{
    while (rows--){
        for (size_t i = 0;i < columns;i++){
            printf("%d,", *(*arr + i));
        }
        arr++;
        putchar('\n');
    }
}
