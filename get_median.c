#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int double_cmp(const void *vp1, const void *vp2)
{
    const double *p1 = (const double *)vp1;
    const double *p2 = (const double *)vp2;
    return *p1 > *p2 ? 1 : *p1 < *p2 ? -1 : 0;
}

double get_median_ret(const double *p_sorted, size_t size)
{
    if (!(size % 2))
        return *(p_sorted + size / 2) + *(p_sorted + size / 2 - 1) / 2.;
    return *(p_sorted + size / 2);
}

double get_median(const double *p, size_t size)
{
    double *p_temp = (double *)malloc(sizeof(double) * size);
    if (!p_temp){
        fprintf(stderr, "out of memory");
        exit(EXIT_FAILURE);
    }
    memcpy(p_temp, p, sizeof(double) * size);
    qsort(p_temp, size, sizeof(double), &double_cmp);
    double ret = get_median_ret(p_temp, size);
    free(p_temp);
    return ret;
}
