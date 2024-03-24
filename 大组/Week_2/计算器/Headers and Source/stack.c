#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
// 栈结构体
struct Stack
{
    char stackName[20];
    struct node* HeadNode;
    size_t size;
};

// 初始化一条队列
struct Stack* initStack(char StackName[20])
{
    struct Stack* Stack = (struct Stack*)malloc(sizeof(struct Stack));
    Stack->size = 0;
    Stack->HeadNode = NULL;
    strcpy(Stack->stackName, StackName);
    return Stack;
}

// 给指定栈添加节点
int addNode(struct Stack* Stack, void* data)
{
    struct node* Node = CreatNode(data);
    Node->next = Stack->HeadNode;
    Stack->HeadNode = Node;
    Stack->size++;
    return 1;
}

// 弹出头节点
void* getNode(struct Stack* Stack)
{
    if (Stack->size == 0)
        return NULL;
    struct node* Node = Stack->HeadNode;
    Stack->size--;
    Stack->HeadNode = Node->next;
    void* Data = Node->Data;
    Node->Data = NULL;
    Node->next = NULL;
    free(Node);
    return Data;
}

int changeData(struct Stack* Stack, void* Data)
{
    return ChangeData(Data, Stack->HeadNode);
}

// 清空栈
int cleanStack(struct Stack* Stack)
{
    struct node* Next = NULL;
    if (Stack->size != 0)
        for (struct node* Node = Stack->HeadNode->next; (Node != NULL); Node = Next)
        {
            Next = Node->next;
            if (!DeletNode(Stack->HeadNode, Node))
                return 0;
        }
    free(Stack->HeadNode);
    Stack->HeadNode = NULL;
    Stack->size = 0;
    free(Stack);
    Stack = NULL;
    return 1;
}

// 获取头节点数据
void* getData(struct Stack* Stack)
{
    if (Stack->size == 0)
        return NULL;
    return Stack->HeadNode->Data;
}