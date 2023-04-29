char *strcpy_1(char *pdest, const char *psource)
{
    char *pdest_old = pdest;
    while (*psource)
        *pdest++ = *psource++;
    *pdest = '\0';
    return pdest_old;
}