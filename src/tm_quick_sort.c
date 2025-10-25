#include "tm_quick_sort.h"
#include <string.h>

static void quickSortRec(void *array, int low, int high, size_t size, CompareFunc cmp)
{
    if (low >= high) return;

    char pivot[size];
    memcpy(pivot, (char *)array + high * size, size);

    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (cmp((char *)array + j * size, pivot) <= 0)
        {
            i++;
            swap((char *)array + i * size, (char *)array + j * size, size);
        }
    }
    swap((char *)array + (i + 1) * size, (char *)array + high * size, size);

    quickSortRec(array, low, i, size, cmp);
    quickSortRec(array, i + 2, high, size, cmp);
}

void quickSort(void *array, size_t n, size_t size, CompareFunc cmp)
{
    if (!array || !cmp || n < 2) return;
    quickSortRec(array, 0, (int)n - 1, size, cmp);
}
