#include <stdio.h>
#include <stdlib.h>
#include "red_black_tree.h"

Status RBT_init(RedBlackTreePtr RBT)
{
    RBT = (RedBlackTreePtr)malloc(sizeof(RedBlackTree));
    if (RBT == NULL)
        return failed;
    RBT->root = NULL;
    return succeed;
}

Status RBT_leftRotate(RedBlackTreePtr RBT, NodePtr node)
{
    NodePtr right = node->right;
    node->right = right->left;
    if (right->left != NULL)
        right->left->parent = node;
    right->parent = node->parent;
    if (node->parent == NULL)
        RBT->root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
    return succeed;
}

Status RBT_rightRotate(RedBlackTreePtr RBT, NodePtr node)
{
    NodePtr left = node->left;
    node->left = left->right;
    if (left->right != NULL)
        left->right->parent = node;
    left->parent = node->parent;
    if (node->parent == NULL)
        RBT->root = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right = node;
    node->parent = left;
    return succeed;
}

NodePtr RBT_createNode(ElemType value, enum Colors color)
{
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->value = value;
    newNode->color = color;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

void RBT_insertFixup(RedBlackTreePtr RBT, NodePtr node)
{
    while (node->parent != NULL && node->parent->color == RED)
    {
        NodePtr grandparent = node->parent->parent;
        if (node->parent == grandparent->left)
        {
            NodePtr uncle = grandparent->right;
            if (uncle != NULL && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    RBT_leftRotate(RBT, node);
                }
                node->parent->color = BLACK;
                grandparent->color = RED;
                RBT_rightRotate(RBT, grandparent);
            }
        }
        else
        {
            NodePtr uncle = grandparent->left;
            if (uncle != NULL && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    RBT_rightRotate(RBT, node);
                }
                node->parent->color = BLACK;
                grandparent->color = RED;
                RBT_leftRotate(RBT, grandparent);
            }
        }
    }
    RBT->root->color = BLACK;
}

Status RBT_insert(RedBlackTreePtr RBT, ElemType value)
{
    NodePtr newNode = RBT_createNode(value, RED);
    if (newNode == NULL)
        return failed;

    NodePtr current = RBT->root;
    NodePtr parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (value < current->value)
            current = current->left;
        else if (value > current->value)
            current = current->right;
        else
        {
            free(newNode);
            return failed;
        }
    }

    newNode->parent = parent;

    if (parent == NULL)
        RBT->root = newNode;
    else if (value < parent->value)
        parent->left = newNode;
    else
        parent->right = newNode;

    RBT_insertFixup(RBT, newNode);

    return succeed;
}

void RBT_transplant(RedBlackTreePtr RBT, NodePtr u, NodePtr v)
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

void RBT_deleteFixup(RedBlackTreePtr RBT, NodePtr x)
{
    while (x != RBT->root && x != NULL && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            NodePtr w = x->parent->right;
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
            NodePtr w = x->parent->left;
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

NodePtr RBT_searchNode(RedBlackTreePtr RBT, ElemType value)
{
    NodePtr current = RBT->root;
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

NodePtr RBT_minimum(NodePtr node)
{
    while (node->left != NULL)
        node = node->left;
    return node;
}

Status RBT_delete(RedBlackTreePtr RBT, ElemType value)
{
    NodePtr node = RBT_searchNode(RBT, value);
    if (node == NULL)
        return failed;

    NodePtr y = node;
    NodePtr x;
    enum Colors yOriginalColor = y->color;

    if (node->left == NULL)
    {
        x = node->right;
        RBT_transplant(RBT, node, node->right);
    }
    else if (node->right == NULL)
    {
        x = node->left;
        RBT_transplant(RBT, node, node->left);
    }
    else
    {
        y = RBT_minimum(node->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == node)
        {
            if (x != NULL)
                x->parent = y;
        }
        else
        {
            RBT_transplant(RBT, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        RBT_transplant(RBT, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    if (yOriginalColor == BLACK)
        RBT_deleteFixup(RBT, x);

    free(node);
    return succeed;
}

Status RBT_search(RedBlackTreePtr RBT, ElemType value)
{
    NodePtr current = RBT->root;
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