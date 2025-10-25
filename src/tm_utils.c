#include "tm_utils.h"

// Swap two elements of arbitrary type
void swap(void *a, void *b, size_t size)
{
    unsigned char *p = (unsigned char *)a;
    unsigned char *q = (unsigned char *)b;
    unsigned char tmp;

    for (size_t i = 0; i < size; i++)
    {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

// Comparison functions for common types
int intCompare(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    return (x > y) - (x < y);
}

int floatCompare(const void *a, const void *b)
{
    float x = *(float *)a;
    float y = *(float *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int doubleCompare(const void *a, const void *b)
{
    double x = *(double *)a;
    double y = *(double *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}
