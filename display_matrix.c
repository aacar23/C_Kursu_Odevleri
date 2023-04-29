#include <stdio.h>

#define rows(a) (sizeof(a) / sizeof(*a))
#define columns(a, smallest_elements_type) (sizeof(*a) / sizeof(smallest_elements_type))


void display_matrix_int(const int *matrix, size_t rows, size_t columns)
{
    while (rows--) {
        for (size_t i = 0;i < columns;i++) {
            printf("%-5d", *matrix++);
        }
        putchar('\n');
        putchar('\n');
    }
}