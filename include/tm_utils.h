#ifndef __TM_UTILS_H
#define __TM_UTILS_H 123

#include <stddef.h>

// Generic swap function
void swap(void *a, void *b, size_t size);

// Common comparison functions
int intCompare(const void *a, const void *b);
int floatCompare(const void *a, const void *b);
int doubleCompare(const void *a, const void *b);

#endif
