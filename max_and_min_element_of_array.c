void swap_pointers(int **a, int **b)
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}

void max_and_min_element_of_array(const int *arr, int **max, int **min, size_t size)
{
    *max = (int *)arr;
    *min = (int *)(arr + 1);
    
    if (**max < **min)
        swap_pointers(max, min);
    
    while (size--)
        
        if (*(arr + size) > **max)
            *max = (int *)(arr + size);
    
        else if (*(arr + size) < **min)
            *min = (int *)(arr + size);
}