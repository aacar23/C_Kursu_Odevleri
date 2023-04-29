char *strpbrk(const char *p, const char *pchars)
{

    while (*p){
        const char *temp_pchars = pchars;
        while (*temp_pchars){
            if (*p == *temp_pchars++)
                return (char *)p;
        }
        p++;
    }
    return NULL;
}