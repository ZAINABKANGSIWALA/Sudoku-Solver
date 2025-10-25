#include "tm_heap_sort.h"
#include <string.h>

static void heapify(void *array, size_t n, size_t i, size_t size, CompareFunc cmp)
{
    size_t largest = i;
    size_t l = 2 * i + 1;
    size_t r = 2 * i + 2;

    if (l < n && cmp((char *)array + l * size, (char *)array + largest * size) > 0)
        largest = l;

    if (r < n && cmp((char *)array + r * size, (char *)array + largest * size) > 0)
        largest = r;

    if (largest != i)
    {
        swap((char *)array + i * size, (char *)array + largest * size, size);
        heapify(array, n, largest, size, cmp);
    }
}

void heapSort(void *array, size_t n, size_t size, CompareFunc cmp)
{
    if (!array || !cmp || n < 2) return;

    for (int i = (int)n / 2 - 1; i >= 0; i--)
        heapify(array, n, i, size, cmp);

    for (int i = (int)n - 1; i >= 0; i--)
    {
        swap(array, (char *)array + i * size, size);
        heapify(array, i, 0, size, cmp);
    }
}
