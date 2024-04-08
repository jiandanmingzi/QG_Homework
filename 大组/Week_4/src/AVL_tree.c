#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define succeed 1
#define failed 0
#define Status int
#define Height int

typedef int ElemType;

typedef struct Node
{
    ElemType value;
    struct Node *left, *right, *parent;
    Height height;
} Node, *NodePtr;

typedef struct AVLTree
{
    NodePtr root;
} AVLTree, *AVLTreePtr;

void AVLT_rotateRight(AVLTreePtr, NodePtr);

void AVLT_rotateLeft(AVLTreePtr, NodePtr);

Height AVLT_HeightFactor(NodePtr);

Status AVLT_init(AVLTreePtr);

Status AVLT_insert(AVLTreePtr, ElemType);

Status AVLT_delete(AVLTreePtr, ElemType);

Status AVLT_search(AVLTreePtr, ElemType);

Status AVLT_preorderI(AVLTreePtr, void (*visit)(NodePtr));

Status AVLT_preorderR(AVLTreePtr, void (*visit)(NodePtr));

Status AVLT_inorderI(AVLTreePtr, void (*visit)(NodePtr));

Status AVLT_inorderR(AVLTreePtr, void (*visit)(NodePtr));

Status AVLT_postorderI(AVLTreePtr, void (*visit)(NodePtr));

Status AVLT_postorderR(AVLTreePtr, void (*visit)(NodePtr));

Status AVLT_levelOrder(AVLTreePtr, void (*visit)(NodePtr));

void AVLT_rebalance(AVLTreePtr, NodePtr, Height, Height);

NodePtr AVLT_createNode(ElemType);

NodePtr AVLT_searchNode(AVLTreePtr, ElemType);

NodePtr AVLT_createNode(ElemType value)
{
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    if (newNode == NULL)
        printf("Memory allocation failed\n");
    else
    {
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        newNode->height = 1;
    }
    return newNode;
}

void AVLT_rotateRight(AVLTreePtr AVL, NodePtr node)
{
    NodePtr left = node->left;
    node->left = left->right;
    if (left->right != NULL)
        left->right->parent = node;
    left->parent = node->parent;
    if (node->parent == NULL)
        AVL->root = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right = node;
    node->parent = left;
}

void AVLT_rotateLeft(AVLTreePtr AVL, NodePtr node)
{
    NodePtr right = node->right;
    node->right = right->left;
    if (right->left != NULL)
        right->left->parent = node;
    right->parent = node->parent;
    if (node->parent == NULL)
        AVL->root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

Height AVLT_HeightFactor(NodePtr Node)
{
    if (Node == NULL)
        return 0;
    Height LHeight = AVLT_HeightFactor(Node->left);
    Height RHeight = AVLT_HeightFactor(Node->right);
    return (LHeight > RHeight ? LHeight : RHeight) + 1;
}

void AVLT_rebalance(AVLTreePtr AVL, NodePtr Node, Height LHeight, Height RHeight)
{
    if (LHeight - RHeight > 1)
    {
        if (AVLT_HeightFactor(Node->left->left) > AVLT_HeightFactor(Node->left->right))
            AVLT_rotateRight(AVL, Node);
        else
        {
            AVLT_rotateLeft(AVL, Node->left);
            AVLT_rotateRight(AVL, Node);
        }
    }
    else if (RHeight - LHeight > 1)
    {
        if (AVLT_HeightFactor(Node->right->right) > AVLT_HeightFactor(Node->right->left))
            AVLT_rotateLeft(AVL, Node);
        else
        {
            AVLT_rotateRight(AVL, Node->right);
            AVLT_rotateLeft(AVL, Node);
        }
    }
}

Status AVLT_search(AVLTreePtr AVL, ElemType value)
{
    NodePtr current = AVL->root;
    while (current != NULL)
    {
        if (current->value == value)
            return succeed;
        else if (current->value > value)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

Status AVLT_init(AVLTreePtr AVL)
{
    AVL = (AVLTreePtr)malloc(sizeof(AVLTree));
    if (AVL == NULL)
        return failed;
    AVL->root = NULL;
    return succeed;
}

Status AVLT_insert(AVLTreePtr AVL, ElemType value)
{
    NodePtr node = AVLT_createNode(value);
    if (node == NULL)
        return failed;
    if (AVL->root == NULL)
    {
        AVL->root = node;
        return succeed;
    }
    NodePtr parent = NULL, current = AVL->root;
    while (current != NULL)
    {
        parent = current;
        if (value < current->value)
            current = current->left;
        else if (value > current->value)
            current = current->right;
        else
            return failed;
    }
    if (value < parent->value)
        parent->left = node;
    else
        parent->right = node;
    node->parent = parent;
    while (parent != NULL)
    {
        parent->height = AVLT_HeightFactor(parent);
        Height LHeight = AVLT_HeightFactor(parent->left);
        Height RHeight = AVLT_HeightFactor(parent->right);
        if (LHeight - RHeight > 1 || RHeight - LHeight > 1)
        {
            AVLT_rebalance(AVL, parent, LHeight, RHeight);
            break;
        }
        parent = parent->parent;
    }
    return succeed;
}

Status AVLT_delete(AVLTreePtr AVL, ElemType value)
{
    NodePtr node = AVLT_searchNode(AVL, value);
    if (node == NULL)
        return failed;
    NodePtr parent = node->parent;
    if (node->left == NULL)
    {
        if (node == AVL->root)
            AVL->root = node->right;
        else if (node == parent->left)
            parent->left = node->right;
        else
            parent->right = node->right;
        if (node->right != NULL)
            node->right->parent = parent;
        free(node);
        node = NULL;
    }
    else if (node->right == NULL)
    {
        if (node == AVL->root)
            AVL->root = node->left;
        else if (node == parent->left)
            parent->left = node->left;
        else
            parent->right = node->left;
        node->left->parent = parent;
        free(node);
        node = NULL;
    }
    else
    {
        NodePtr successor = node->right;
        while (successor->left != NULL)
            successor = successor->left;
        node->value = successor->value;
        parent = successor->parent;
        if (successor == parent->left)
            parent->left = successor->right;
        else
            parent->right = successor->right;
        if (successor->right != NULL)
            successor->right->parent = parent;
    }
    while (parent != NULL)
    {
        parent->height = AVLT_HeightFactor(parent);
        Height LHeight = AVLT_HeightFactor(parent->left);
        Height RHeight = AVLT_HeightFactor(parent->right);
        if (LHeight - RHeight > 1 || RHeight - LHeight > 1)
            AVLT_rebalance(AVL, parent, LHeight, RHeight);
        parent = parent->parent;
    }
    return succeed;
}