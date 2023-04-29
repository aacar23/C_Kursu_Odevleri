void* mymemchr(const void *vp, int val, size_t sz)
{
    const unsigned char * p = (const unsigned char *)vp;
    for (size_t i = 0;i < sz;i++)
        if (*(p + i) == (unsigned char)val)
            return (unsigned char *)(vp + i);

    return NULL;
}