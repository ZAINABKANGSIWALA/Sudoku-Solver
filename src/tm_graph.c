#ifndef __TM_GRAPH_C
#define __TM_GRAPH_C 123

#include <stdio.h>
#include <stdlib.h>
#include "tm_graph.h"
#include "tm_sll.h"

// Create graph
Graph *createGraph(int (*cmp)(const void *, const void *), bool directed, bool *success)
{
    if (success) *success = false;
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph) return NULL;
    graph->nodes = createSinglyLinkedList(success);
    if (!*success)
    {
        free(graph);
        return NULL;
    }
    graph->cmp = cmp;
    graph->directed = directed;
    if (success) *success = true;
    return graph;
}

// Helper: find vertex node by data
static GraphNode *findVertexNode(Graph *graph, void *data)
{
    int size = getSizeOfSinglyLinkedList(graph->nodes);
    for (int i = 0; i < size; i++)
    {
        GraphNode *v = (GraphNode *)getFromSinglyLinkedList(graph->nodes, i, NULL);
        if (graph->cmp(v->data, data) == 0)
            return v;
    }
    return NULL;
}

// Add vertex
void addVertex(Graph *graph, void *data, bool *success)
{
    if (success) *success = false;
    if (!graph) return;
    if (findVertexNode(graph, data) != NULL) return; // already exists

    GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
    if (!node) return;
    node->data = data;
    node->adjList = createSinglyLinkedList(success);
    if (!*success)
    {
        free(node);
        return;
    }
    addToSinglyLinkedList(graph->nodes, node, success);
}

// Add edge
void addEdge(Graph *graph, void *from, void *to, bool *success)
{
    if (success) *success = false;
    if (!graph) return;
    GraphNode *vFrom = findVertexNode(graph, from);
    GraphNode *vTo = findVertexNode(graph, to);
    if (!vFrom || !vTo) return;

    // check if edge already exists
    if (!hasEdge(graph, from, to))
        addToSinglyLinkedList(vFrom->adjList, vTo, NULL);

    if (!graph->directed)
    {
        if (!hasEdge(graph, to, from))
            addToSinglyLinkedList(vTo->adjList, vFrom, NULL);
    }
    if (success) *success = true;
}

// Check if edge exists
bool hasEdge(Graph *graph, void *from, void *to)
{
    GraphNode *vFrom = findVertexNode(graph, from);
    GraphNode *vTo = findVertexNode(graph, to);
    if (!vFrom || !vTo) return false;

    int size = getSizeOfSinglyLinkedList(vFrom->adjList);
    for (int i = 0; i < size; i++)
    {
        GraphNode *adj = (GraphNode *)getFromSinglyLinkedList(vFrom->adjList, i, NULL);
        if (adj == vTo) return true;
    }
    return false;
}

// Get adjacency list
SinglyLinkedList *getAdjacencyList(Graph *graph, void *data, bool *success)
{
    if (success) *success = false;
    GraphNode *v = findVertexNode(graph, data);
    if (!v) return NULL;
    if (success) *success = true;
    return v->adjList;
}

// Check if vertex exists
bool hasVertex(Graph *graph, void *data)
{
    return findVertexNode(graph, data) != NULL;
}

// Remove edge
void removeEdge(Graph *graph, void *from, void *to, bool *success)
{
    if (success) *success = false;
    GraphNode *vFrom = findVertexNode(graph, from);
    GraphNode *vTo = findVertexNode(graph, to);
    if (!vFrom || !vTo) return;

    int size = getSizeOfSinglyLinkedList(vFrom->adjList);
    for (int i = 0; i < size; i++)
    {
        GraphNode *adj = (GraphNode *)getFromSinglyLinkedList(vFrom->adjList, i, NULL);
        if (adj == vTo)
        {
            removeFromSinglyLinkedList(vFrom->adjList, i, NULL);
            break;
        }
    }

    if (!graph->directed)
    {
        size = getSizeOfSinglyLinkedList(vTo->adjList);
        for (int i = 0; i < size; i++)
        {
            GraphNode *adj = (GraphNode *)getFromSinglyLinkedList(vTo->adjList, i, NULL);
            if (adj == vFrom)
            {
                removeFromSinglyLinkedList(vTo->adjList, i, NULL);
                break;
            }
        }
    }

    if (success) *success = true;
}

// Remove vertex
void removeVertex(Graph *graph, void *data, bool *success)
{
    if (success) *success = false;
    GraphNode *v = findVertexNode(graph, data);
    if (!v) return;

    // Remove all edges pointing to this vertex
    int nSize = getSizeOfSinglyLinkedList(graph->nodes);
    for (int i = 0; i < nSize; i++)
    {
        GraphNode *other = (GraphNode *)getFromSinglyLinkedList(graph->nodes, i, NULL);
        if (other == v) continue;
        int adjSize = getSizeOfSinglyLinkedList(other->adjList);
        for (int j = 0; j < adjSize; j++)
        {
            GraphNode *adj = (GraphNode *)getFromSinglyLinkedList(other->adjList, j, NULL);
            if (adj == v)
            {
                removeFromSinglyLinkedList(other->adjList, j, NULL);
                break;
            }
        }
    }

    clearSinglyLinkedList(v->adjList);
    free(v->adjList);

    // Remove vertex from nodes list
    for (int i = 0; i < nSize; i++)
    {
        GraphNode *node = (GraphNode *)getFromSinglyLinkedList(graph->nodes, i, NULL);
        if (node == v)
        {
            removeFromSinglyLinkedList(graph->nodes, i, NULL);
            break;
        }
    }

    free(v);
    if (success) *success = true;
}

// Clear graph
void clearGraph(Graph *graph)
{
    if (!graph) return;
    int size = getSizeOfSinglyLinkedList(graph->nodes);
    for (int i = 0; i < size; i++)
    {
        GraphNode *v = (GraphNode *)getFromSinglyLinkedList(graph->nodes, i, NULL);
        clearSinglyLinkedList(v->adjList);
        free(v->adjList);
        free(v);
    }
    clearSinglyLinkedList(graph->nodes);
}

// Destroy graph
void destroyGraph(Graph *graph)
{
    if (!graph) return;
    clearGraph(graph);
    free(graph);
}

#endif
