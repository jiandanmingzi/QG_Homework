#include <stdio.h>
#include <stdlib.h>
#include "red_black_tree.h"

RedBlackTreePtr RBT_init()
{
    RedBlackTreePtr RBT = (RedBlackTreePtr)malloc(sizeof(RedBlackTree));
    if (RBT != NULL)
        RBT->root = NULL;
    return RBT;
}

Status RBT_leftRotate(RedBlackTreePtr RBT, RBT_NodePtr RBT_Node)
{
    RBT_NodePtr right = RBT_Node->right;
    RBT_Node->right = right->left;
    if (right->left != NULL)
        right->left->parent = RBT_Node;
    right->parent = RBT_Node->parent;
    if (RBT_Node->parent == NULL)
        RBT->root = right;
    else if (RBT_Node == RBT_Node->parent->left)
        RBT_Node->parent->left = right;
    else
        RBT_Node->parent->right = right;
    right->left = RBT_Node;
    RBT_Node->parent = right;
    return succeed;
}

Status RBT_rightRotate(RedBlackTreePtr RBT, RBT_NodePtr RBT_Node)
{
    RBT_NodePtr left = RBT_Node->left;
    RBT_Node->left = left->right;
    if (left->right != NULL)
        left->right->parent = RBT_Node;
    left->parent = RBT_Node->parent;
    if (RBT_Node->parent == NULL)
        RBT->root = left;
    else if (RBT_Node == RBT_Node->parent->right)
        RBT_Node->parent->right = left;
    else
        RBT_Node->parent->left = left;
    left->right = RBT_Node;
    RBT_Node->parent = left;
    return succeed;
}

RBT_NodePtr RBT_createRBT_Node(ElemType value, enum Colors color)
{
    RBT_NodePtr newRBT_Node = (RBT_NodePtr)malloc(sizeof(RBT_Node));
    if (newRBT_Node == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newRBT_Node->value = value;
    newRBT_Node->color = color;
    newRBT_Node->left = NULL;
    newRBT_Node->right = NULL;
    newRBT_Node->parent = NULL;
    return newRBT_Node;
}

void RBT_insertFixup(RedBlackTreePtr RBT, RBT_NodePtr RBT_Node)
{
    while (RBT_Node->parent != NULL && RBT_Node->parent->color == RED)
    {
        RBT_NodePtr grandparent = RBT_Node->parent->parent;
        if (RBT_Node->parent == grandparent->left)
        {
            RBT_NodePtr uncle = grandparent->right;
            if (uncle != NULL && uncle->color == RED)
            {
                RBT_Node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                RBT_Node = grandparent;
            }
            else
            {
                if (RBT_Node == RBT_Node->parent->right)
                {
                    RBT_Node = RBT_Node->parent;
                    RBT_leftRotate(RBT, RBT_Node);
                }
                RBT_Node->parent->color = BLACK;
                grandparent->color = RED;
                RBT_rightRotate(RBT, grandparent);
            }
        }
        else
        {
            RBT_NodePtr uncle = grandparent->left;
            if (uncle != NULL && uncle->color == RED)
            {
                RBT_Node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                RBT_Node = grandparent;
            }
            else
            {
                if (RBT_Node == RBT_Node->parent->left)
                {
                    RBT_Node = RBT_Node->parent;
                    RBT_rightRotate(RBT, RBT_Node);
                }
                RBT_Node->parent->color = BLACK;
                grandparent->color = RED;
                RBT_leftRotate(RBT, grandparent);
            }
        }
    }
    RBT->root->color = BLACK;
}

Status RBT_insert(RedBlackTreePtr RBT, ElemType value)
{
    RBT_NodePtr newRBT_Node = RBT_createRBT_Node(value, RED);
    if (newRBT_Node == NULL)
        return failed;

    RBT_NodePtr current = RBT->root;
    RBT_NodePtr parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (value < current->value)
            current = current->left;
        else if (value > current->value)
            current = current->right;
        else
        {
            free(newRBT_Node);
            return failed;
        }
    }

    newRBT_Node->parent = parent;

    if (parent == NULL)
        RBT->root = newRBT_Node;
    else if (value < parent->value)
        parent->left = newRBT_Node;
    else
        parent->right = newRBT_Node;

    RBT_insertFixup(RBT, newRBT_Node);

    return succeed;
}

void RBT_transplant(RedBlackTreePtr RBT, RBT_NodePtr u, RBT_NodePtr v)
{
    if (u->parent == NULL)
        RBT->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

void RBT_deleteFixup(RedBlackTreePtr RBT, RBT_NodePtr x)
{
    while (x != RBT->root && x != NULL && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            RBT_NodePtr w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RBT_leftRotate(RBT, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RBT_rightRotate(RBT, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                RBT_leftRotate(RBT, x->parent);
                x = RBT->root;
            }
        }
        else
        {
            RBT_NodePtr w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RBT_rightRotate(RBT, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    RBT_leftRotate(RBT, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RBT_rightRotate(RBT, x->parent);
                x = RBT->root;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

RBT_NodePtr RBT_searchRBT_Node(RedBlackTreePtr RBT, ElemType value)
{
    RBT_NodePtr current = RBT->root;
    while (current != NULL)
    {
        if (value == current->value)
            return current;
        else if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}

RBT_NodePtr RBT_minimum(RBT_NodePtr RBT_Node)
{
    while (RBT_Node->left != NULL)
        RBT_Node = RBT_Node->left;
    return RBT_Node;
}

Status RBT_delete(RedBlackTreePtr RBT, ElemType value)
{
    RBT_NodePtr RBT_Node = RBT_searchRBT_Node(RBT, value);
    if (RBT_Node == NULL)
        return failed;

    RBT_NodePtr y = RBT_Node;
    RBT_NodePtr x;
    enum Colors yOriginalColor = y->color;

    if (RBT_Node->left == NULL)
    {
        x = RBT_Node->right;
        RBT_transplant(RBT, RBT_Node, RBT_Node->right);
    }
    else if (RBT_Node->right == NULL)
    {
        x = RBT_Node->left;
        RBT_transplant(RBT, RBT_Node, RBT_Node->left);
    }
    else
    {
        y = RBT_minimum(RBT_Node->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == RBT_Node)
        {
            if (x != NULL)
                x->parent = y;
        }
        else
        {
            RBT_transplant(RBT, y, y->right);
            y->right = RBT_Node->right;
            y->right->parent = y;
        }
        RBT_transplant(RBT, RBT_Node, y);
        y->left = RBT_Node->left;
        y->left->parent = y;
        y->color = RBT_Node->color;
    }

    if (yOriginalColor == BLACK)
        RBT_deleteFixup(RBT, x);

    free(RBT_Node);
    return succeed;
}

Status RBT_search(RedBlackTreePtr RBT, ElemType value)
{
    RBT_NodePtr current = RBT->root;
    while (current != NULL)
    {
        if (value == current->value)
            return succeed;
        else if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }
    return failed;
}