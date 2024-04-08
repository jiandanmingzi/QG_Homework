#ifndef AVL_TREE_H
#define AVL_TREE_H

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

#endif