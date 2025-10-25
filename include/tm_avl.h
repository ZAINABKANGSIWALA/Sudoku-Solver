#ifndef __TM_AVL_H
#define __TM_AVL_H 123

#include <tm_common.h>

typedef struct __$_tm_avl_node
{
    void *data;
    struct __$_tm_avl_node *left;
    struct __$_tm_avl_node *right;
    int height;
} AVLNode;

typedef struct __$_tm_avl_tree
{
    AVLNode *root;
    int (*cmp)(const void *, const void *); // comparison function
} AVLTree;

// Create AVL tree (requires comparison function)
AVLTree *createAVLTree(int (*cmp)(const void *, const void *), bool *success);

// Insert an element
void insertIntoAVLTree(AVLTree *tree, void *data, bool *success);

// Remove an element
void removeFromAVLTree(AVLTree *tree, void *data, bool *success);

// Search for an element
void *searchInAVLTree(AVLTree *tree, void *data, bool *success);

// Traversals
void inOrderTraversal(AVLTree *tree, void (*callback)(void *));
void preOrderTraversal(AVLTree *tree, void (*callback)(void *));
void postOrderTraversal(AVLTree *tree, void (*callback)(void *));

// Clear tree
void clearAVLTree(AVLTree *tree);

// Destroy tree
void destroyAVLTree(AVLTree *tree);

#endif
