char *mystrcat(char *p1, const char *p2)
{
    char *ret_p = p1;
    while(*p1++)
        ;
    p1--;
    while ((*p1++ = *p2++))
        ;
    return ret_p;
}