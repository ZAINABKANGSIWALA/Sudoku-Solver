#ifndef __TM_QUEUE__C
#define __TM_QUEUE__C 123
#include <stdio.h>
#include <stdlib.h>
#include <tm_queue.h>
#include <tm_sll.h>

// Create a new queue
Queue *createQueue(bool *success)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        if (success) *success = false;
        return NULL;
    }
    queue->singlyLinkedList = createSinglyLinkedList(success);
    if (!success || queue->singlyLinkedList == NULL)
    {
        free(queue);
        if (success) *success = false;
        return NULL;
    }
    if (success) *success = true;
    return queue;
}

// Add element at the end of the queue (enqueue)
void addToQueue(Queue *queue, void *ptr, bool *success)
{
    if (success) *success = false;
    if (queue == NULL || queue->singlyLinkedList == NULL) return;

    // Add to the end of linked list
    addToSinglyLinkedList(queue->singlyLinkedList, ptr, success);
}

// Remove element from the front of the queue (dequeue)
void *removeFromQueue(Queue *queue, bool *success)
{
    if (success) *success = false;
    if (queue == NULL || queue->singlyLinkedList == NULL) return NULL;
    if (isQueueEmpty(queue)) return NULL;

    // Remove from the start of linked list
    return removeFromSinglyLinkedList(queue->singlyLinkedList, 0, success);
}

// Get current size of queue
int getSizeOfQueue(Queue *queue)
{
    if (queue == NULL || queue->singlyLinkedList == NULL) return 0;
    return getSizeOfSinglyLinkedList(queue->singlyLinkedList);
}

// Get element at the front without removing
void *elementAtFrontOfQueue(Queue *queue, bool *success)
{
    if (success) *success = false;
    if (queue == NULL || queue->singlyLinkedList == NULL) return NULL;
    if (isQueueEmpty(queue)) return NULL;

    return getFromSinglyLinkedList(queue->singlyLinkedList, 0, success);
}

// Check if queue is empty
bool isQueueEmpty(Queue *queue)
{
    if (queue == NULL || queue->singlyLinkedList == NULL) return true;
    return getSizeOfSinglyLinkedList(queue->singlyLinkedList) == 0;
}

// Clear all elements in the queue
void clearQueue(Queue *queue)
{
    if (queue == NULL || queue->singlyLinkedList == NULL) return;
    clearSinglyLinkedList(queue->singlyLinkedList);
}

// Destroy the queue and free memory
void destroyQueue(Queue *queue)
{
    if (queue == NULL) return;
    if (queue->singlyLinkedList != NULL)
    {
        destroySinglyLinkedList(queue->singlyLinkedList);
    }
    free(queue);
}

#endif
