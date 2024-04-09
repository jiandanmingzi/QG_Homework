#ifndef AVL_TREE_H
#define AVL_TREE_H

#define true 1
#define false 0
#define succeed 1
#define failed 0
#define Status int
#define Height int

typedef int ElemType;

typedef struct AVL_Node
{
    ElemType value;
    struct AVL_Node *left, *right, *parent;
    Height height;
} AVL_Node, *AVL_NodePtr;

typedef struct AVLTree
{
    AVL_NodePtr root;
} AVLTree, *AVLTreePtr;

void AVLT_rotateRight(AVLTreePtr, AVL_NodePtr);

void AVLT_rotateLeft(AVLTreePtr, AVL_NodePtr);

Height AVLT_HeightFactor(AVL_NodePtr);

AVLTreePtr AVLT_init();

Status AVLT_insert(AVLTreePtr, ElemType);

Status AVLT_delete(AVLTreePtr, ElemType);

Status AVLT_search(AVLTreePtr, ElemType);

Status AVLT_preorderI(AVLTreePtr, void (*visit)(AVL_NodePtr));

Status AVLT_preorderR(AVL_NodePtr, void (*visit)(AVL_NodePtr));

Status AVLT_inorderI(AVLTreePtr, void (*visit)(AVL_NodePtr));

Status AVLT_inorderR(AVL_NodePtr, void (*visit)(AVL_NodePtr));

Status AVLT_postorderI(AVLTreePtr, void (*visit)(AVL_NodePtr));

Status AVLT_postorderR(AVL_NodePtr, void (*visit)(AVL_NodePtr));

Status AVLT_levelOrder(AVLTreePtr, void (*visit)(AVL_NodePtr));

void AVLT_rebalance(AVLTreePtr, AVL_NodePtr, Height, Height);

AVL_NodePtr AVLT_createAVL_Node(ElemType);

AVL_NodePtr AVLT_searchAVL_Node(AVLTreePtr, ElemType);

#endif