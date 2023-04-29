char *strchr1(const char *p, int c)
{
    while (*p) {
        if (*p == c)
            return (char *)p;
        p++;
    }
    if (c == '\0')
        return (char *)p;
    return NULL;
}