char *strrchr1(const char *p, int c)
{
    const char *ret_p = NULL;
    while(*p){
        if (*p == c)
            ret_p = p;
        p++;
    }
    if (c == '\0')
        return (char *)p;
    return (char *)ret_p;
}