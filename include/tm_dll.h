#ifndef __TM_DLL__H
#define __TM_DLL__H 123
#include <tm_common.h>

typedef struct __$_tm_dll_node
{
    void *ptr;
    struct __$_tm_dll_node *next;
    struct __$_tm_dll_node *prev;
} DoublyLinkedListNode;

typedef struct __$_tm_dll
{
    struct __$_tm_dll_node *start;
    struct __$_tm_dll_node *end;
    int size;
} DoublyLinkedList;

DoublyLinkedList *createDoublyLinkedList(bool *success);

void destroyDoublyLinkedList(DoublyLinkedList *list);

int getSizeOfDoublyLinkedList(DoublyLinkedList *list);

void addToDoublyLinkedList(DoublyLinkedList *list, void *ptr, bool *success);

void insertIntoDoublyLinkedList(DoublyLinkedList *list, int index, void *ptr, bool *success);

void *removeFromDoublyLinkedList(DoublyLinkedList *list, int index, bool *success);

void clearDoublyLinkedList(DoublyLinkedList *list);

void appendToDoublyLinkedList(DoublyLinkedList *target, DoublyLinkedList *source, bool *success);

void *getFromDoublyLinkedList(DoublyLinkedList *list, int index, bool *success);

#endif
