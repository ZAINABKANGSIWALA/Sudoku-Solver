#include "tm_insertion_sort.h"
#include <string.h>

void insertionSort(void *array, size_t n, size_t size, CompareFunc cmp)
{
    if (!array || !cmp || n < 2) return;

    for (size_t i = 1; i < n; i++)
    {
        char buffer[size];
        memcpy(buffer, (char *)array + i * size, size);
        int j = (int)i - 1;
        while (j >= 0 && cmp((char *)array + j * size, buffer) > 0)
        {
            memcpy((char *)array + (j + 1) * size, (char *)array + j * size, size);
            j--;
        }
        memcpy((char *)array + (j + 1) * size, buffer, size);
    }
}
