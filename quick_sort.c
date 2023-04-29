void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int *partation(int *start, int *end)
{
    int *p = start;
    while (start < end){
        if (*start < *end){
            swap (p, start);
            p++;
        }
        start++;
    }
    swap(p, end);
    return p;
}

void quick_sort(int *start, int *end)
{
    if (start < end){
        int *pivot = partation(start, end);
        quick_sort(start, pivot - 1);
        quick_sort(pivot + 1, end);
    }
}