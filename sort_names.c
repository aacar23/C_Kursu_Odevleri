#include <stdio.h>
#include <string.h>
#define asize(a) (sizeof(a) / sizeof(*a))

void swap_char_pointers(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

char **pivot_partation(char **start, char **end)
{
    char **pivot = start;

    while (start < end) {

        if (strlen(*start) < strlen(*end))
            swap_char_pointers(pivot++, start);
        else if (strlen(*start) == strlen(*end) && strcmp(*start, *end) < 0)
            swap_char_pointers(pivot++, start);

        start++;

    }

    swap_char_pointers(pivot, end);
    return pivot;
}

void quick_sort_char_pointer_array(char **start, char **end)
{
    if (start < end){

        char **pivot = pivot_partation(start, end);

        quick_sort_char_pointer_array(pivot + 1, end);
        quick_sort_char_pointer_array(start, pivot - 1);
        
    }
}

void print_names(const char *const *names, size_t size)
{
    while (size--)
        printf("%s ", *names++);
    
    putchar('\n');
}


int main(void)
{
    char * names[] = {"Ayse", "Fatma", "Yunus", "Yasin", "Mustafa", "Ali", "Ruzgar", "Toprak", "Ozgur", "Hatice", "Aynur", "Memduh", "Emine", "Esma", "Nazli", "Nureddin", "Kemal", "Ayta", "Aliye", "Ekmeleddin"};
    quick_sort_char_pointer_array(names, names + asize(names) - 1);
    print_names((const char * const *)names, asize(names));
}