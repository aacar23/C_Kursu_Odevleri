#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char *urlify(char *dest, const char *source, const char *replacement)
{
    int dest_count = 0;
    for (int i = 0;*(source + i);i++){
        if (*(source + i) == ' '){
            memcpy(dest + dest_count, replacement, strlen(replacement));
            dest_count += strlen(replacement);
        }
        else{
            *(dest + dest_count++) = *(source + i);
        }
    }
    return dest;
}

int is_permutation_of_a_palindrome(const char *str)
{
    int counts[26] = {0};
    int ones = 0;
    for (int i = 0;*(str + i);i++){
        if (isupper(*(str + i)))
            ++*(counts + *(str + i) - 65);
        else if (islower(*(str + i)))
            ++*(counts + *(str + i) - 97);
    }
    for (int i = 0;i < 26;i++)
        if (*(counts + i) == 1)
            ones++;
    if (ones > 1)
        return 0;
    for (int i = 0;i < 26;i++)
        if (*(counts + i) != 1 && (*(counts + i) % 2))
            return 0;

    return 1;
}

int zero_or_one_change_occured(const char *str1, const char *str2)
{
    int difference = 0;
    for(size_t idx1 = 0, idx2 = 0, str1_size = strlen(str1), str2_size = strlen(str2);idx1 < str1_size && idx2 < str2_size;){
        if (*(str1 + idx1) == *(str2 + idx2))
            idx1++, idx2++;
        else if (*(str1 + idx1) != *(str2 + idx2) && str1_size > str2_size)
            idx1++, difference++;
        else if (*(str1 + idx1) != *(str2 + idx2) && str1_size < str2_size)
            idx2++, difference++;
        else if (*(str1 + idx1) != *(str2 + idx2) && str1_size == str2_size)
            idx1++, idx2++, difference++;
    }
    return difference <= 1;
}



char *compress_string(char *str)
{
    size_t size = strlen(str);
    int counts[26][2] = {0};
    for (size_t i = 0;i < size;i++)
        ++*(*(counts + toupper(*(str + i)) - 97) + isupper(*(str + i)));
    int temp = 1;
    size_t start_index = 0;
    size_t end_index = 0;
    for (;end_index < size - 1;){

        if (*(str + start_index) == *(str + start_index + 1)){
            temp++;
            memmove(str + start_index, str + start_index + 1, strlen(str) - start_index);
            end_index++;
        }
        else{
            memmove(str + start_index + 1, str + start_index, strlen(str) - start_index);
            *(str + start_index + 1) = temp + 48;
            start_index += 2;
            temp = 1;
        }
    }
    return str;
}

int *zero_matrix(int *matrix, size_t rows, size_t columns)
{
    int *copy = malloc(rows * columns * sizeof(int));
    memcpy(copy, matrix, rows * columns * sizeof(int));
    for (size_t i = 0;i < rows;i++){
        for (size_t t = 0;t < columns;t++)
            if (!*(copy + columns * i + t)){
                for (size_t r = 0;r < rows;r++)
                    *(matrix + columns * r + t) = 0;
                for (size_t r = 0;r < columns;r++)
                    *(matrix + columns * i + r) = 0;
            }
    }
    free(copy);
    return matrix;
}

int string_rotation(const char *str1, const char *str2)
{
    char *rotations = malloc(strlen(str1) * 2 + 1);
    strcpy(rotations, str1);
    strcat(rotations, str1);
    if (strlen(str2) != strlen(str1))
        return 0;
    return !!strstr(rotations, str2);
}