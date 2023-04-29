int mystrcmp(const char *p1, const char *p2)
{
    do{
        if (*p1 > *p2)
            return *p1 - *p2;
        if (*p1 < *p2)
            return *p1 - *p2;
    } while (*p1++ && *p2++);
    return 0;
}