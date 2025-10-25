#include <stdlib.h>
#include "tm_map.h"

// Create a new map
Map *createMap(int (*cmp)(const void *, const void *), bool *success)
{
    if (success) *success = false;
    Map *map = (Map *)malloc(sizeof(Map));
    if (!map) return NULL;

    map->list = createSinglyLinkedList(success);
    if (!map->list)
    {
        free(map);
        return NULL;
    }

    map->cmp = cmp;
    if (success) *success = true;
    return map;
}

// Put key-value pair (add or update)
void put(Map *map, void *key, void *value, bool *success)
{
    if (success) *success = false;
    if (!map || !map->list) return;

    int size = getSizeOfSinglyLinkedList(map->list);
    for (int i = 0; i < size; i++)
    {
        MapEntry *entry = (MapEntry *)getFromSinglyLinkedList(map->list, i, NULL);
        if (map->cmp(entry->key, key) == 0)
        {
            entry->value = value; // Update value
            if (success) *success = true;
            return;
        }
    }

    MapEntry *entry = (MapEntry *)malloc(sizeof(MapEntry));
    entry->key = key;
    entry->value = value;
    addToSinglyLinkedList(map->list, entry, success);
}

// Get value by key
void *get(Map *map, void *key, bool *success)
{
    if (success) *success = false;
    if (!map || !map->list) return NULL;

    int size = getSizeOfSinglyLinkedList(map->list);
    for (int i = 0; i < size; i++)
    {
        MapEntry *entry = (MapEntry *)getFromSinglyLinkedList(map->list, i, NULL);
        if (map->cmp(entry->key, key) == 0)
        {
            if (success) *success = true;
            return entry->value;
        }
    }
    return NULL;
}

// Remove a key
void removeKey(Map *map, void *key, bool *success)
{
    if (success) *success = false;
    if (!map || !map->list) return;

    int size = getSizeOfSinglyLinkedList(map->list);
    for (int i = 0; i < size; i++)
    {
        MapEntry *entry = (MapEntry *)getFromSinglyLinkedList(map->list, i, NULL);
        if (map->cmp(entry->key, key) == 0)
        {
            removeFromSinglyLinkedList(map->list, i, success);
            free(entry);
            if (success) *success = true;
            return;
        }
    }
}

// Check if key exists
bool hasKey(Map *map, void *key)
{
    if (!map || !map->list) return false;
    int size = getSizeOfSinglyLinkedList(map->list);
    for (int i = 0; i < size; i++)
    {
        MapEntry *entry = (MapEntry *)getFromSinglyLinkedList(map->list, i, NULL);
        if (map->cmp(entry->key, key) == 0)
            return true;
    }
    return false;
}

// Number of entries
int getSizeOfMap(Map *map)
{
    if (!map || !map->list) return 0;
    return getSizeOfSinglyLinkedList(map->list);
}

// Clear map
void clearMap(Map *map)
{
    if (!map || !map->list) return;

    int size = getSizeOfSinglyLinkedList(map->list);
    for (int i = 0; i < size; i++)
    {
        MapEntry *entry = (MapEntry *)getFromSinglyLinkedList(map->list, i, NULL);
        free(entry);
    }
    clearSinglyLinkedList(map->list);
}

// Destroy map
void destroyMap(Map *map)
{
    if (!map) return;
    clearMap(map);
    destroySinglyLinkedList(map->list);
    free(map);
}
