#include <stdlib.h>
#include <stdio.h>

char *generate_a_password_linux(size_t length_of_password)
{
    char *str = (char *)calloc(length_of_password + 1, sizeof(char));
    if (!str){
        fprintf(stderr, "out of memory");
        exit(EXIT_FAILURE);
    }
    FILE *f = fopen("/dev/urandom", "r");
    for (size_t i = 0;i < length_of_password;i++){
        unsigned int ascii_char;
        fread(&ascii_char, sizeof(unsigned int), 1, f);
        *(str + i) = (int)(ascii_char % 95) + 32;
    }
    fclose(f);
    return str;
}

char **fill_array_with_random_passwords_linux(const char **dest, size_t number_of_elements, size_t length_of_passwords)
{
    for (size_t i = 0;i < number_of_elements;i++)
        *(dest + i) = generate_a_password_linux(length_of_passwords);
    return (char **)dest;
}

void free_all_char_pointer_array_elements(char **arr, size_t number_of_elements)
{
    while (number_of_elements--)
        free(*arr++);
}
