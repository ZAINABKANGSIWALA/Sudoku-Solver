#include "tm_selection_sort.h"

void selectionSort(void *array, size_t n, size_t size, CompareFunc cmp)
{
    if (!array || !cmp || n < 2) return;

    for (size_t i = 0; i < n - 1; i++)
    {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (cmp((char *)array + j * size, (char *)array + min_idx * size) < 0)
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            swap((char *)array + i * size, (char *)array + min_idx * size, size);
        }
    }
}
