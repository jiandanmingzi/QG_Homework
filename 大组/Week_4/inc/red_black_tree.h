#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#define true 1
#define false 0
#define succeed 1
#define failed 0
#define Status int

typedef int ElemType;

enum Colors
{
    RED,
    BLACK
};

typedef struct Node
{
    ElemType value;
    enum Colors color;
    struct Node *left, *right, *parent;
} Node, *NodePtr;

typedef struct RedBlackTree
{
    NodePtr root;
} RedBlackTree, *RedBlackTreePtr;

Status RBT_init(RedBlackTreePtr);

Status RBT_leftRotate(RedBlackTreePtr, NodePtr);

Status RBT_rightRotate(RedBlackTreePtr, NodePtr);

NodePtr RBT_createNode(ElemType, enum Colors);

void RBT_insertFixup(RedBlackTreePtr, NodePtr);

Status RBT_insert(RedBlackTreePtr, ElemType);

void RBT_transplant(RedBlackTreePtr, NodePtr, NodePtr);

void RBT_deleteFixup(RedBlackTreePtr, NodePtr);

NodePtr RBT_searchNode(RedBlackTreePtr, ElemType);

NodePtr RBT_minimum(NodePtr);

Status RBT_delete(RedBlackTreePtr, ElemType);

Status RBT_search(RedBlackTreePtr, ElemType);

Status RBT_preorderI(RedBlackTreePtr, void (*visit)(NodePtr));

Status RBT_preorderR(RedBlackTreePtr, void (*visit)(NodePtr));

Status RBT_inorderI(RedBlackTreePtr, void (*visit)(NodePtr));

Status RBT_inorderR(RedBlackTreePtr, void (*visit)(NodePtr));

Status RBT_postorderI(RedBlackTreePtr, void (*visit)(NodePtr));

Status RBT_postorderR(RedBlackTreePtr, void (*visit)(NodePtr));

Status RBT_levelorder(RedBlackTreePtr, void (*visit)(NodePtr));

#endif