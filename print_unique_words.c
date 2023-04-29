int is_unique(const char *str)
{
    if (!*str)
        return 0;
    int alpha_count[26] = {0};
    while (alpha_count[*str - 'a']++, *++str)
        ;
    for (int i = 0;i < 26;i++)
        if (alpha_count[i] > 1)
            return 0;
    return 1;
}

void print_unique_words(const char * const *str_array, size_t size)
{
    while (size--)
        if (is_unique(*(str_array + size)))
            printf("%s ", *(str_array + size));
    putchar('\n');
}