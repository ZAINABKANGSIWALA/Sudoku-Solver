#ifndef __TM_GRAPH_H
#define __TM_GRAPH_H 123

#include <tm_common.h>
#include "tm_sll.h" // use your generic SLL for adjacency list

typedef struct __$_tm_graph_node
{
    void *data;                  // vertex data
    SinglyLinkedList *adjList;   // adjacency list (list of pointers to other nodes)
} GraphNode;

typedef struct __$_tm_graph
{
    SinglyLinkedList *nodes;     // list of GraphNode*
    int (*cmp)(const void *, const void *); // comparison function for data
    bool directed;               // directed or undirected
} Graph;

// Create graph
Graph *createGraph(int (*cmp)(const void *, const void *), bool directed, bool *success);

// Add vertex
void addVertex(Graph *graph, void *data, bool *success);

// Add edge
void addEdge(Graph *graph, void *from, void *to, bool *success);

// Remove vertex
void removeVertex(Graph *graph, void *data, bool *success);

// Remove edge
void removeEdge(Graph *graph, void *from, void *to, bool *success);

// Get adjacency list for a vertex
SinglyLinkedList *getAdjacencyList(Graph *graph, void *data, bool *success);

// Check if vertex exists
bool hasVertex(Graph *graph, void *data);

// Check if edge exists
bool hasEdge(Graph *graph, void *from, void *to);

// Clear graph
void clearGraph(Graph *graph);

// Destroy graph
void destroyGraph(Graph *graph);

#endif
