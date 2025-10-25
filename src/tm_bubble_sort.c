#include "tm_bubble_sort.h"

void bubbleSort(void *array, size_t n, size_t size, CompareFunc cmp)
{
    if (!array || !cmp || n < 2) return;

    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - i - 1; j++)
        {
            void *elem1 = (char *)array + j * size;
            void *elem2 = (char *)array + (j + 1) * size;
            if (cmp(elem1, elem2) > 0)
            {
                swap(elem1, elem2, size); // from tm_utils
            }
        }
    }
}
