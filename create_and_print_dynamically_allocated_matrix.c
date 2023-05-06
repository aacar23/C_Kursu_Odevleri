#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define randomize() srand((unsigned)(time(NULL)));
#define malloc(bytes) (my_malloc(bytes))


#define ROWS 50
#define COLUMNS 100
#define MODULUS 100

void *my_malloc(size_t bytes)
{
    void *vp = (malloc)(bytes);
    if (!vp){
        fprintf(stderr, "out of memory");
        exit(EXIT_FAILURE);
    }
    return vp;
}

void set_array_random_linux(int *arr, int less, size_t number_of_elements)
{
    FILE *f = fopen("/dev/urandom", "r");
    while (number_of_elements--){
        int element;
        fread(&element, sizeof(element), 1, f);
        *arr++ = element % less;
    }
    fclose(f);
}

void set_array_random_standard(int *arr, int less, size_t number_of_elements)
{
    while (number_of_elements--)
        *arr++ = rand() % less;
}

void fill_a_generically_array_size_typed_matrix(int **matrix, int rows, int columns, int modulus, void (*setter_func)(int *arr, int less, size_t number_of_elements))
{
    for (int i = 0;i < rows;i++){
        *(matrix + i) = (int *)malloc(columns * sizeof(int));
        (*setter_func)(*(matrix + i), modulus, columns);
    }
}


int **create_dynamically_allocated_generically_array_size_typed_matrix(int rows, int columns, int modulus, void (*setter_func)(int *arr, int less, size_t number_of_elements))
{
    int **new_matrix = (int **)malloc(rows * sizeof(int *));
    fill_a_generically_array_size_typed_matrix(new_matrix, rows, columns, modulus, setter_func);
    return new_matrix;
}

void free_all_matrix_elements(int **matrix, size_t rows)
{
    for (size_t i = 0;i < rows;i++){
        free(*(matrix + i));
    }
}

void free_matrix(int **matrix, size_t rows)
{
    free_all_matrix_elements(matrix, rows);
    free(matrix);
}


void print_matrix(const int * const *matrix, size_t rows, size_t columns)
{
    while (rows--){
        for (size_t i = 0;i < columns;i++)
            printf("%d,", *((*matrix) + i));
        matrix++;
        putchar('\n');
    }
}