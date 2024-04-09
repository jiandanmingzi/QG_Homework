#include <stdio.h>
#include <stdlib.h>
#include "binary_sort_tree.h"

BinarySortTreePtr BST_init()
{
    BinarySortTreePtr BST = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
    if (BST != NULL)
        BST->root = NULL;
    return BST;
}

Status BST_insert(BinarySortTreePtr BST, ElemType value)
{
    if (BST == NULL)
        return failed;
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    if (node == NULL)
        return failed;
    node->value = value;
    node->left = node->right = NULL;
    if (BST->root == NULL)
    {
        BST->root = node;
        return succeed;
    }
    NodePtr parent = NULL, current = BST->root;
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
    return succeed;
}

Status BST_delete(BinarySortTreePtr BST, ElemType value)
{
    if (BST == NULL || BST->root == NULL)
        return failed;
    NodePtr parent = NULL, current = BST->root;
    while (current != NULL && current->value != value)
    {
        parent = current;
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }
    if (current == NULL)
        return failed;
    if (current->left != NULL && current->right != NULL)
    {
        NodePtr minParent = current, min = current->right;
        while (min->left != NULL)
        {
            minParent = min;
            min = min->left;
        }
        current->value = min->value;
        parent = minParent;
        current = min;
    }
    NodePtr child = NULL;
    if (current->left != NULL)
        child = current->left;
    else if (current->right != NULL)
        child = current->right;
    if (parent == NULL)
        BST->root = child;
    else if (parent->left == current)
        parent->left = child;
    else
        parent->right = child;
    free(current);
    return succeed;
}

Status BST_search(BinarySortTreePtr BST, ElemType value)
{
    if (BST == NULL || BST->root == NULL)
        return false;
    NodePtr current = BST->root;
    while (current != NULL && current->value != value)
    {
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }
    return current != NULL;
}

Status BST_preorderI(BinarySortTreePtr BST, void (*visit)(NodePtr))
{
    if (BST == NULL || BST->root == NULL)
        return failed;
    NodePtr stack[100];
    int top = -1;
    stack[++top] = BST->root;
    while (top != -1)
    {
        NodePtr current = stack[top--];
        visit(current);
        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }
    return succeed;
}

Status BST_preorderR(NodePtr current, void (*visit)(NodePtr))
{
    visit(current);
    if (current->left != NULL)
        BST_preorderR(current->left, visit);
    if (current->right != NULL)
        BST_preorderR(current->right, visit);
    return succeed;
}

Status BST_inorderI(BinarySortTreePtr BST, void (*visit)(NodePtr))
{
    if (BST == NULL || BST->root == NULL)
        return failed;
    NodePtr stack[100];
    int top = -1;
    NodePtr current = BST->root;
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

Status BST_inorderR(NodePtr current, void (*visit)(NodePtr))
{
    if (current != NULL)
    {
        BST_inorderR(current->left, visit);
        visit(current);
        BST_inorderR(current->right, visit);
    }
    return succeed;
}

Status BST_postorderI(BinarySortTreePtr BST, void (*visit)(NodePtr))
{
    if (BST == NULL || BST->root == NULL)
        return failed;
    NodePtr stack[100];
    int top = -1;
    NodePtr current = BST->root;
    NodePtr lastVisit = NULL;
    while (current != NULL || top != -1)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top];
        if (current->right == NULL || current->right == lastVisit)
        {
            visit(current);
            lastVisit = current;
            top--;
            current = NULL;
        }
        else
            current = current->right;
    }
    return succeed;
}

Status BST_postorderR(NodePtr current, void (*visit)(NodePtr))
{
    if (current != NULL)
    {
        BST_postorderR(current->left, visit);
        BST_postorderR(current->right, visit);
        visit(current);
    }
    return succeed;
}

Status BST_levelOrder(BinarySortTreePtr BST, void (*visit)(NodePtr))
{
    if (BST == NULL || BST->root == NULL)
        return failed;
    NodePtr current[100],kids[100];
    current[0] = BST->root;
    int currentNums = 1,kidsNums = 0;
    while (currentNums!=0)
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
        currentNums = kidsNums;
        for (int i = 0; i < kidsNums; i++)
            current[i] = kids[i];
        kidsNums = 0;
    }
    return succeed;
}