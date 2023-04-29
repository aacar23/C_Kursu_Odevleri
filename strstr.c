char *strstr1(const char *p1, const char *p2)
{
    while (*p1){
        if (*p1 == *p2){
            int i;
            for (i = 0;*(p2 + i) != '\0' && *(p1 + i) && *(p1 + i) == *(p2 + i);i++)
                ;
            if (*(p2 + i) == '\0')
                return (char *)p1;
        }
        p1++;
    }
    return NULL;
}