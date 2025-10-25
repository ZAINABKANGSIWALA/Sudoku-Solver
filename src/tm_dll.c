#ifndef __TM_DLL__C
#define __TM_DLL__C 123
#include <tm_dll.h>
#include <stdlib.h>

DoublyLinkedList *createDoublyLinkedList(bool *success)
{
    if(success) *success = false;
    DoublyLinkedList *list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if(list == NULL) return NULL;
    list->start = NULL;
    list->end = NULL;
    list->size = 0;
    if(success) *success = true;
    return list;
}

void destroyDoublyLinkedList(DoublyLinkedList *list)
{
    if(list == NULL) return;
    clearDoublyLinkedList(list);
    free(list);
}

int getSizeOfDoublyLinkedList(DoublyLinkedList *list)
{
    if(list == NULL) return 0;
    return list->size;
}

void addToDoublyLinkedList(DoublyLinkedList *list, void *ptr, bool *success)
{
    if(success) *success = false;
    if(list == NULL) return;
    DoublyLinkedListNode *node = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
    if(node == NULL) return;
    node->ptr = ptr;
    node->next = NULL;
    node->prev = list->end;

    if(list->start == NULL)
    {
        list->start = node;
        list->end = node;
    }
    else
    {
        list->end->next = node;
        list->end = node;
    }
    list->size++;
    if(success) *success = true;
}

void insertIntoDoublyLinkedList(DoublyLinkedList *list, int index, void *ptr, bool *success)
{
    if(success) *success = false;
    if(list == NULL || index < 0 || index > list->size) return;
    if(index == list->size)
    {
        addToDoublyLinkedList(list, ptr, success);
        return;
    }

    DoublyLinkedListNode *node = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
    if(node == NULL) return;
    node->ptr = ptr;

    if(index == 0)
    {
        node->next = list->start;
        node->prev = NULL;
        list->start->prev = node;
        list->start = node;
    }
    else
    {
        DoublyLinkedListNode *p = list->start;
        int x = 0;
        while(x < index)
        {
            p = p->next;
            x++;
        }
        node->next = p;
        node->prev = p->prev;
        p->prev->next = node;
        p->prev = node;
    }
    list->size++;
    if(success) *success = true;
}

void *removeFromDoublyLinkedList(DoublyLinkedList *list, int index, bool *success)
{
    if(success) *success = false;
    if(list == NULL || index < 0 || index >= list->size) return NULL;

    DoublyLinkedListNode *p = list->start;
    int x = 0;
    while(x < index)
    {
        p = p->next;
        x++;
    }

    void *ptr = p->ptr;
    if(list->start == p && list->end == p)
    {
        list->start = NULL;
        list->end = NULL;
    }
    else if(list->start == p)
    {
        list->start = p->next;
        list->start->prev = NULL;
    }
    else if(list->end == p)
    {
        list->end = p->prev;
        list->end->next = NULL;
    }
    else
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    free(p);
    list->size--;
    if(success) *success = true;
    return ptr;
}

void clearDoublyLinkedList(DoublyLinkedList *list)
{
    if(list == NULL) return;
    DoublyLinkedListNode *node;
    while(list->start != NULL)
    {
        node = list->start;
        list->start = list->start->next;
        free(node);
    }
    list->end = NULL;
    list->size = 0;
}

void appendToDoublyLinkedList(DoublyLinkedList *target, DoublyLinkedList *source, bool *success)
{
    if(success) *success = false;
    if(target == NULL) return;
    if(source == NULL || source->size == 0)
    {
        if(success) *success = true;
        return;
    }

    DoublyLinkedListNode *s = NULL, *e = NULL, *t = source->start;
    bool done = true;

    while(t != NULL)
    {
        DoublyLinkedListNode *node = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
        if(node == NULL) { done = false; break; }
        node->ptr = t->ptr;
        node->next = NULL;
        node->prev = e;
        if(s == NULL) { s = node; e = node; }
        else { e->next = node; e = node; }
        t = t->next;
    }

    if(!done)
    {
        while(s != NULL)
        {
            DoublyLinkedListNode *temp = s;
            s = s->next;
            free(temp);
        }
        return;
    }

    if(target->start == NULL)
    {
        target->start = s;
        target->end = e;
        target->size = source->size;
    }
    else
    {
        target->end->next = s;
        s->prev = target->end;
        target->end = e;
        target->size += source->size;
    }

    if(success) *success = true;
}

void *getFromDoublyLinkedList(DoublyLinkedList *list, int index, bool *success)
{
    if(success) *success = false;
    if(list == NULL || index < 0 || index >= list->size) return NULL;
    DoublyLinkedListNode *node = list->start;
    int x = 0;
    while(x < index)
    {
        node = node->next;
        x++;
    }
    if(success) *success = true;
    return node->ptr;
}

#endif
