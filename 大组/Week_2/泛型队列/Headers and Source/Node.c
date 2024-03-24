#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    void* Data;       // 链表节点存储的数据
    struct node* next; // 指向下一个节点的指针
};

// 创建新节点
struct node* CreatNode(void* data)
{
    struct node* Node = NULL;
    Node = (struct node*)malloc(sizeof(struct node));
    if (Node != NULL)
    {
        Node->Data = data;
        Node->next = NULL;
    }
    return Node;
}

// 添加节点
struct node* AddNode(void* Data, struct node* last)
{
    struct node* Node = NULL;
    Node = (struct node*)malloc(sizeof(struct node));
    if (Node != NULL)
    {
        Node->next = last->next;
        Node->Data = Data;
        last->next = Node;
    }
    return Node;
}

// 删除节点
int DeletNode(struct node* last, struct node* Node)
{
    last->next = Node->next;
    Node->next = NULL;
    Node->Data = NULL;
    free(Node);
    Node = NULL;
    if (Node == NULL)
        return 1;
    else
        return 0;
}

// 修改节点数据
int ChangeData(void* Data, struct node* Node)
{
    Node->Data = Data;
    if (Node->Data == Data)
        return 1;
    else
        return 0;
}

// 交换节点位置
void swap(struct node* First, struct node* Second, struct node* FirstLast)
{
    struct node* temp = Second->next;
    FirstLast->next = Second;
    Second->next = First;
    First->next = temp;
}