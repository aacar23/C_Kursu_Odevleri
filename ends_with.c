int ends_with(const char *p1, const char *p2)
{
    while (*p1) {
        if (*p1 == *p2) {
            int i;
            for (i = 0; *(p2 + i); i++)
                if (*(p1 + i) != *(p2 + i))
                    goto out;
            if (*(p1 + i) == '\0')
                return 1;
        }
        out:
        p1++;
    }
    return 0;
}
