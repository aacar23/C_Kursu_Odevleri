#include <stdlib.h>
#include <string.h>

int double_cmp(const void *vp1, const void *vp2)
{
    double *p1 = (double *)vp1;
    double *p2 = (double *)vp2;
    return *p1 > *p2 ? 1 : *p1 < *p2 ? -1 : 0;
}

double get_median_ret(const double *p_sorted, size_t size)
{
    if (!(size % 2))
        return *(p_sorted + size / 2)+ *(p_sorted + size / 2 - 1) / 2.;
    return *(p_sorted + size / 2);
}

double get_median(const double *p, size_t size)
{
    double *p_temp = (double *)malloc(sizeof(double) * size);
    if (!p_temp)
        exit(EXIT_FAILURE);
    memcpy(p_temp, p, sizeof(double) * size);
    qsort(p_temp, size, sizeof(double), &double_cmp);
    double ret = get_median_ret(p_temp, size);
    free(p_temp);
    return ret;
}
