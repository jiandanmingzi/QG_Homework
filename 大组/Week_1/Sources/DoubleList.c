#include "DoubleList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct DoubleList
{
    struct DoubleList *last; // 指向上一个节点的指针
    char Data[20];           // 链表节点存储的数据
    struct DoubleList *next; // 指向下一个节点的指针
};

struct DoubleList *CreatHead(char List_Name[20]) // 创建新链表
{
    struct DoubleList *headList = NULL;
    headList = (struct DoubleList *)malloc(sizeof(struct DoubleList));
    if (headList != NULL)
    {
        strcpy(headList->Data, List_Name);
        headList->next = NULL;
    }
    return headList;
}

struct DoubleList *AddNode(char Data[20], struct DoubleList *last) // 添加节点
{
    struct DoubleList *Node = NULL;
    Node = (struct DoubleList *)malloc(sizeof(struct DoubleList));
    if (Node != NULL)
    {
        Node->last = last;
        Node->next = last->next;
        strcpy(Node->Data, Data);
        last->next = Node;
    }
    return Node;
}

int DeletNode(struct DoubleList *Node) // 删除节点
{
    Node->last->next = Node->next;
    Node->next->last = Node->last;
    Node->next = NULL;
    Node->last = NULL;
    free(Node);
    Node = NULL;
    if (Node == NULL)
        return 1;
    else
        return 0;
}

int ChangeData(char *Data, struct DoubleList *Node) // 修改节点数据
{
    strcpy(Node->Data, Data);
    if (Node->Data == Data)
        return 1;
    else
        return 0;
}

void swap(struct DoubleList *First, struct DoubleList *Second) // 交换节点位置
{
    struct DoubleList *temp = Second->next;
    First->last->next = Second;
    Second->last = First->last;
    Second->next = First;
    First->last = Second;
    First->next = temp;
    if (temp != NULL)
        temp->last = First;
}
