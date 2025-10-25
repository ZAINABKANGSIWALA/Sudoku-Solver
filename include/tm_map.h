#ifndef __TM_MAP_H
#define __TM_MAP_H 123

#include <tm_common.h>
#include "tm_sll.h"

// Generic Map Entry
typedef struct {
    void *key;
    void *value;
} MapEntry;

// Generic Map
typedef struct {
    SinglyLinkedList *list;       // List of MapEntry*
    int (*cmp)(const void *, const void *); // Key comparison function
} Map;

// Create a new map
Map *createMap(int (*cmp)(const void *, const void *), bool *success);

// Add or update a key-value pair
void put(Map *map, void *key, void *value, bool *success);

// Get value by key
void *get(Map *map, void *key, bool *success);

// Remove a key-value pair
void removeKey(Map *map, void *key, bool *success);

// Check if map contains a key
bool hasKey(Map *map, void *key);

// Get the number of entries in the map
int getSizeOfMap(Map *map);

// Clear all entries
void clearMap(Map *map);

// Destroy map and free memory
void destroyMap(Map *map);

#endif
