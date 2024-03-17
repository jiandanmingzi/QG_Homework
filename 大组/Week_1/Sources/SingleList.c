#ifndef SingleList_C
#define SingleList_C
#include "SingleList.h"
struct SingleList
{
    char Data[20];       // 链表节点存储的数据
    struct SingleList *next; // 指向下一个节点的指针
} ;

struct SingleList *CreatHead(char *List_Name) // 创建新链表
{
    struct SingleList *headList = NULL;
    headList = (struct SingleList *)malloc(sizeof(struct SingleList *));
    if (headList != NULL)
    {
        strcpy(headList->Data,List_Name);
        headList->next = NULL;
    }
    return headList;
}

struct SingleList *AddNode(char *Data, struct SingleList *last) // 添加节点
{
    struct SingleList *Node = NULL;
    Node = (struct SingleList *)malloc(sizeof(struct SingleList *));
    if (Node != NULL)
    {
        Node->next = last->next;
        strcpy(Node->Data, Data);
        last->next = Node;
    }
    return Node;
}

int DeletNode(struct SingleList *last, struct SingleList *Node) // 删除节点
{
    last->next = Node->next;
    Node->next = NULL;
    free(Node);
    Node = NULL;
    if (Node == NULL)
        return 1;
    else
        return 0;
}

int ChangeData(char *Data, struct SingleList *Node) // 修改节点数据
{
    strcpy(Node->Data, Data);
    if (Node->Data == Data)
        return 1;
    else
        return 0;
}

void swap(struct SingleList *First, struct SingleList *Second, struct SingleList *FirstLast) // 交换节点位置
{
    struct SingleList *temp = Second->next;
    FirstLast->next = Second;
    Second->next = First;
    First->next = temp;
}