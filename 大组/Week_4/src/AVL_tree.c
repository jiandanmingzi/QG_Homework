#include <stdio.h>
#include <stdlib.h>
#include "AVL_tree.h"

AVL_NodePtr AVLT_createAVL_Node(ElemType value)
{
    AVL_NodePtr newAVL_Node = (AVL_NodePtr)malloc(sizeof(AVL_Node));
    if (newAVL_Node == NULL)
        printf("Memory allocation failed\n");
    else
    {
        newAVL_Node->value = value;
        newAVL_Node->left = NULL;
        newAVL_Node->right = NULL;
        newAVL_Node->parent = NULL;
        newAVL_Node->height = 1;
    }
    return newAVL_Node;
}

void AVLT_rotateRight(AVLTreePtr AVL, AVL_NodePtr AVL_Node)
{
    AVL_NodePtr left = AVL_Node->left;
    AVL_Node->left = left->right;
    if (left->right != NULL)
        left->right->parent = AVL_Node;
    left->parent = AVL_Node->parent;
    if (AVL_Node->parent == NULL)
        AVL->root = left;
    else if (AVL_Node == AVL_Node->parent->right)
        AVL_Node->parent->right = left;
    else
        AVL_Node->parent->left = left;
    left->right = AVL_Node;
    AVL_Node->parent = left;
}

void AVLT_rotateLeft(AVLTreePtr AVL, AVL_NodePtr AVL_Node)
{
    AVL_NodePtr right = AVL_Node->right;
    AVL_Node->right = right->left;
    if (right->left != NULL)
        right->left->parent = AVL_Node;
    right->parent = AVL_Node->parent;
    if (AVL_Node->parent == NULL)
        AVL->root = right;
    else if (AVL_Node == AVL_Node->parent->left)
        AVL_Node->parent->left = right;
    else
        AVL_Node->parent->right = right;
    right->left = AVL_Node;
    AVL_Node->parent = right;
}

Height AVLT_HeightFactor(AVL_NodePtr AVL_Node)
{
    if (AVL_Node == NULL)
        return 0;
    Height LHeight = AVLT_HeightFactor(AVL_Node->left);
    Height RHeight = AVLT_HeightFactor(AVL_Node->right);
    return (LHeight > RHeight ? LHeight : RHeight) + 1;
}

void AVLT_rebalance(AVLTreePtr AVL, AVL_NodePtr AVL_Node, Height LHeight, Height RHeight)
{
    if (LHeight - RHeight > 1)
    {
        if (AVLT_HeightFactor(AVL_Node->left->left) > AVLT_HeightFactor(AVL_Node->left->right))
            AVLT_rotateRight(AVL, AVL_Node);
        else
        {
            AVLT_rotateLeft(AVL, AVL_Node->left);
            AVLT_rotateRight(AVL, AVL_Node);
        }
    }
    else if (RHeight - LHeight > 1)
    {
        if (AVLT_HeightFactor(AVL_Node->right->right) > AVLT_HeightFactor(AVL_Node->right->left))
            AVLT_rotateLeft(AVL, AVL_Node);
        else
        {
            AVLT_rotateRight(AVL, AVL_Node->right);
            AVLT_rotateLeft(AVL, AVL_Node);
        }
    }
}

Status AVLT_search(AVLTreePtr AVL, ElemType value)
{
    AVL_NodePtr current = AVL->root;
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

AVLTreePtr AVLT_init()
{
    AVLTreePtr AVL = (AVLTreePtr)malloc(sizeof(AVLTree));
    if (AVL != NULL)
        AVL->root = NULL;
    return AVL;
}

Status AVLT_insert(AVLTreePtr AVL, ElemType value)
{
    AVL_NodePtr AVL_Node = AVLT_createAVL_Node(value);
    if (AVL_Node == NULL)
        return failed;
    if (AVL->root == NULL)
    {
        AVL->root = AVL_Node;
        return succeed;
    }
    AVL_NodePtr parent = NULL, current = AVL->root;
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
        parent->left = AVL_Node;
    else
        parent->right = AVL_Node;
    AVL_Node->parent = parent;
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
    AVL_NodePtr AVL_Node = AVLT_searchAVL_Node(AVL, value);
    if (AVL_Node == NULL)
        return failed;
    AVL_NodePtr parent = AVL_Node->parent;
    if (AVL_Node->left == NULL)
    {
        if (AVL_Node == AVL->root)
            AVL->root = AVL_Node->right;
        else if (AVL_Node == parent->left)
            parent->left = AVL_Node->right;
        else
            parent->right = AVL_Node->right;
        if (AVL_Node->right != NULL)
            AVL_Node->right->parent = parent;
        free(AVL_Node);
        AVL_Node = NULL;
    }
    else if (AVL_Node->right == NULL)
    {
        if (AVL_Node == AVL->root)
            AVL->root = AVL_Node->left;
        else if (AVL_Node == parent->left)
            parent->left = AVL_Node->left;
        else
            parent->right = AVL_Node->left;
        AVL_Node->left->parent = parent;
        free(AVL_Node);
        AVL_Node = NULL;
    }
    else
    {
        AVL_NodePtr successor = AVL_Node->right;
        while (successor->left != NULL)
            successor = successor->left;
        AVL_Node->value = successor->value;
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

AVL_NodePtr AVLT_searchAVL_Node(AVLTreePtr AVL, ElemType value)
{
    AVL_NodePtr current = AVL->root;
    while (current != NULL)
    {
        if (current->value == value)
            return current;
        else if (current->value > value)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}

Status AVLT_preorderI(AVLTreePtr AVL, void (*visit)(AVL_NodePtr))
{
    AVL_NodePtr current = AVL->root;
    AVL_NodePtr stack[100];
    int top = -1;
    while (current != NULL || top != -1)
    {
        while (current != NULL)
        {
            visit(current);
            stack[++top] = current;
            current = current->left;
        }
        if (top != -1)
        {
            current = stack[top--];
            current = current->right;
        }
    }
    return succeed;
}

Status AVLT_preorderR(AVL_NodePtr current, void (*visit)(AVL_NodePtr))
{
    if (current != NULL)
    {
        visit(current);
        AVLT_preorderR(current->left, visit);
        AVLT_preorderR(current->right, visit);
    }
    return succeed;
}

Status AVLT_inorderI(AVLTreePtr AVL, void (*visit)(AVL_NodePtr))
{
    AVL_NodePtr current = AVL->root;
    AVL_NodePtr stack[100];
    int top = -1;
    while (current != NULL || top != -1)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        if (top != -1)
        {
            current = stack[top--];
            visit(current);
            current = current->right;
        }
    }
    return succeed;
}

Status AVLT_inorderR(AVL_NodePtr current, void (*visit)(AVL_NodePtr))
{
    if (current != NULL)
    {
        AVLT_inorderR(current->left, visit);
        visit(current);
        AVLT_inorderR(current->right, visit);
    }
    return succeed;
}

Status AVLT_postorderI(AVLTreePtr AVL, void (*visit)(AVL_NodePtr))
{
    AVL_NodePtr current = AVL->root;
    AVL_NodePtr stack[100];
    int top = -1;
    AVL_NodePtr lastVisited = NULL;
    while (current != NULL || top != -1)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top];
        if (current->right == NULL || current->right == lastVisited)
        {
            visit(current);
            lastVisited = current;
            top--;
            current = NULL;
        }
        else
            current = current->right;
    }
    return succeed;
}

Status AVLT_postorderR(AVL_NodePtr current, void (*visit)(AVL_NodePtr))
{
    if (current != NULL)
    {
        AVLT_postorderR(current->left, visit);
        AVLT_postorderR(current->right, visit);
        visit(current);
    }
    return succeed;
}

Status AVLT_levelOrder(AVLTreePtr AVL, void (*visit)(AVL_NodePtr))
{
    if (AVL == NULL || AVL->root == NULL)
        return failed;
    AVL_NodePtr current[100], kids[100];
    current[0] = AVL->root;
    int currentNums = 1, kidsNums = 0;
    while (currentNums != 0)
    {
        for (int i = 0; i < currentNums; i++)
        {
            visit(current[i]);
            if (current[i]->left != NULL)
                kids[kidsNums++] = current[i]->left;
            if (current[i]->right != NULL)
                kids[kidsNums++] = current[i]->right;
        }
        printf("\n");
        for (int i = 0; i < kidsNums; i++)
            current[i] = kids[i];
        currentNums = kidsNums;
        kidsNums = 0;
    }
    return succeed;
}