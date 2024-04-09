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

typedef struct RBT_Node
{
    ElemType value;
    enum Colors color;
    struct RBT_Node *left, *right, *parent;
} RBT_Node, *RBT_NodePtr;

typedef struct RedBlackTree
{
    RBT_NodePtr root;
} RedBlackTree, *RedBlackTreePtr;

RedBlackTreePtr RBT_init();

Status RBT_leftRotate(RedBlackTreePtr, RBT_NodePtr);

Status RBT_rightRotate(RedBlackTreePtr, RBT_NodePtr);

RBT_NodePtr RBT_createRBT_Node(ElemType, enum Colors);

void RBT_insertFixup(RedBlackTreePtr, RBT_NodePtr);

Status RBT_insert(RedBlackTreePtr, ElemType);

void RBT_transplant(RedBlackTreePtr, RBT_NodePtr, RBT_NodePtr);

void RBT_deleteFixup(RedBlackTreePtr, RBT_NodePtr);

RBT_NodePtr RBT_searchRBT_Node(RedBlackTreePtr, ElemType);

RBT_NodePtr RBT_minimum(RBT_NodePtr);

Status RBT_delete(RedBlackTreePtr, ElemType);

Status RBT_search(RedBlackTreePtr, ElemType);

Status RBT_levelorder(RedBlackTreePtr, void (*visit)(RBT_NodePtr));

#endif