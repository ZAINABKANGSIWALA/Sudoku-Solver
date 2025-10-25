#ifndef __TM_AVL_C
#define __TM_AVL_C 123

#include <stdio.h>
#include <stdlib.h>
#include <tm_avl.h>

// Helper: get height of node
static int height(AVLNode *node)
{
    return node ? node->height : 0;
}

// Helper: max
static int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Create a new AVL node
static AVLNode *createAVLNode(void *data)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    if (!node) return NULL;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate
static AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
static AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get balance factor
static int getBalance(AVLNode *node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

// Internal insert
static AVLNode *insertNode(AVLNode *node, void *data, int (*cmp)(const void *, const void *), bool *success)
{
    if (!node)
    {
        if(success) *success = true;
        return createAVLNode(data);
    }

    int comparison = cmp(data, node->data);
    if (comparison < 0)
        node->left = insertNode(node->left, data, cmp, success);
    else if (comparison > 0)
        node->right = insertNode(node->right, data, cmp, success);
    else
    {
        // duplicate
        if(success) *success = false;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && cmp(data, node->left->data) < 0)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && cmp(data, node->right->data) > 0)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && cmp(data, node->left->data) > 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && cmp(data, node->right->data) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Internal min value node
static AVLNode *minValueNode(AVLNode *node)
{
    AVLNode *current = node;
    while(current->left != NULL)
        current = current->left;
    return current;
}

// Internal remove
static AVLNode *removeNode(AVLNode *root, void *data, int (*cmp)(const void *, const void *), bool *success)
{
    if (!root)
    {
        if(success) *success = false;
        return root;
    }

    int comparison = cmp(data, root->data);
    if (comparison < 0)
        root->left = removeNode(root->left, data, cmp, success);
    else if (comparison > 0)
        root->right = removeNode(root->right, data, cmp, success);
    else
    {
        // Node with one or no child
        if (root->left == NULL || root->right == NULL)
        {
            AVLNode *temp = root->left ? root->left : root->right;
            if (!temp)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp; // copy contents
            free(temp);
        }
        else
        {
            // Node with two children
            AVLNode *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = removeNode(root->right, temp->data, cmp, success);
        }
        if(success) *success = true;
    }

    if (!root) return root;

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Balancing
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Internal search
static void *searchNode(AVLNode *root, void *data, int (*cmp)(const void *, const void *), bool *success)
{
    if (!root)
    {
        if(success) *success = false;
        return NULL;
    }
    int comparison = cmp(data, root->data);
    if (comparison == 0)
    {
        if(success) *success = true;
        return root->data;
    }
    else if (comparison < 0)
        return searchNode(root->left, data, cmp, success);
    else
        return searchNode(root->right, data, cmp, success);
}

// Internal clear
static void clearNode(AVLNode *node)
{
    if (!node) return;
    clearNode(node->left);
    clearNode(node->right);
    free(node);
}

// Internal traversal
static void inOrderNode(AVLNode *node, void (*callback)(void *))
{
    if (!node) return;
    inOrderNode(node->left, callback);
    callback(node->data);
    inOrderNode(node->right, callback);
}

static void preOrderNode(AVLNode *node, void (*callback)(void *))
{
    if (!node) return;
    callback(node->data);
    preOrderNode(node->left, callback);
    preOrderNode(node->right, callback);
}

static void postOrderNode(AVLNode *node, void (*callback)(void *))
{
    if (!node) return;
    postOrderNode(node->left, callback);
    postOrderNode(node->right, callback);
    callback(node->data);
}

// Public functions
AVLTree *createAVLTree(int (*cmp)(const void *, const void *), bool *success)
{
    AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));
    if (!tree)
    {
        if(success) *success = false;
        return NULL;
    }
    tree->root = NULL;
    tree->cmp = cmp;
    if(success) *success = true;
    return tree;
}

void insertIntoAVLTree(AVLTree *tree, void *data, bool *success)
{
    if (!tree) { if(success) *success = false; return; }
    tree->root = insertNode(tree->root, data, tree->cmp, success);
}

void removeFromAVLTree(AVLTree *tree, void *data, bool *success)
{
    if (!tree) { if(success) *success = false; return; }
    tree->root = removeNode(tree->root, data, tree->cmp, success);
}

void *searchInAVLTree(AVLTree *tree, void *data, bool *success)
{
    if (!tree) { if(success) *success = false; return NULL; }
    return searchNode(tree->root, data, tree->cmp, success);
}

void inOrderTraversal(AVLTree *tree, void (*callback)(void *))
{
    if (!tree) return;
    inOrderNode(tree->root, callback);
}

void preOrderTraversal(AVLTree *tree, void (*callback)(void *))
{
    if (!tree) return;
    preOrderNode(tree->root, callback);
}

void postOrderTraversal(AVLTree *tree, void (*callback)(void *))
{
    if (!tree) return;
    postOrderNode(tree->root, callback);
}

void clearAVLTree(AVLTree *tree)
{
    if (!tree) return;
    clearNode(tree->root);
    tree->root = NULL;
}

void destroyAVLTree(AVLTree *tree)
{
    if (!tree) return;
    clearNode(tree->root);
    free(tree);
}

#endif
