int str_count(const char *p, int c)
{
    int count = 0;
    while (*p)
        if (*p++ == c)
            count++;
    return count;
}