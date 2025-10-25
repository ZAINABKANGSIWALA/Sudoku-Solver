#ifndef __TM_QUICK_SORT_H
#define __TM_QUICK_SORT_H 123

#include <stddef.h>
#include "tm_utils.h"

typedef int (*CompareFunc)(const void *a, const void *b);

void quickSort(void *array, size_t n, size_t size, CompareFunc cmp);

#endif
