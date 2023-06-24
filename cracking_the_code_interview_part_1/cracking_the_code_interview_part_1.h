#if !defined CRACKING_THE_CODE_INTERVIEW_PART_1_H
#define CRACKING_THE_CODE_INTERVIEW_PART_1_H

#include <stddef.h>

char *urlify(char *dest, const char *source, const char *replacement);
int is_permutation_of_a_palindrome(const char *str);
int zero_or_one_change_occured(const char *str1, const char *str2);
char *compress_string(char *str);
int *zero_matrix(int *matrix, size_t rows, size_t columns);
int string_rotation(const char *str1, const char *str2);

#endif