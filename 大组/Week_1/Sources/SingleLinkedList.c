#include "SingleLinkedList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct SingleListOp
{
    int size;                // 记录节点个数
    struct SingleList *head; // 指向头节点的指针
    struct SingleList *end;  // 指向尾节点的指针
};

int GetSize(struct SingleListOp *target) // 获取链表长度
{

    int FastCnt = 0, SlowCnt = 0;
    if (target->head != NULL)
    {
        struct SingleList *FastNode = target->head, *SlowNode = target->head;
        while (FastNode->next != NULL)
        {
            FastNode = FastNode->next;
            SlowNode = SlowNode->next;
            if (FastNode->next != NULL)
            {
                FastNode = FastNode->next;
                if (FastNode == SlowNode)
                {
                    if (FastNode == target->head)
                        target->size = 0;
                    break;
                }
            }
        }
        if ((FastNode->next != NULL) && (target->size != 0))
        {
            FastCnt = 0;
            FastNode = target->head;
            while (FastNode != SlowNode)
            {
                FastNode = FastNode->next;
                SlowNode = SlowNode->next;
                FastCnt++;
            }
            SlowCnt = 0;
            while (SlowNode->next != FastNode)
            {
                SlowNode = SlowNode->next;
                SlowCnt++;
            }
            target->size = SlowCnt + FastCnt;
        }
    }
    return target->size;
}

struct SingleList *GetNode(struct SingleListOp *target, int cnt) // 获取特定位置的节点
{
    struct SingleList *temp = NULL;
    if (cnt <= GetSize(target))
    {
        temp = target->head->next;
        for (size_t i = 1; i < cnt; i++)
            temp = temp->next;
    }
    return temp;
}

struct SingleList *AddFromEnd(struct SingleListOp *target, char *Data) // 从尾添加
{
    struct SingleList *end = NULL;
    end = AddNode(Data, target->end);
    target->end = end;
    target->size++;
    return end;
}

struct SingleList *AddFromHead(struct SingleListOp *target, char *Data) // 从头添加
{
    struct SingleList *temp = NULL;
    temp = AddNode(Data, target->head);
    if (temp != NULL)
        target->size++;
    return temp;
}

int DelFromEnd(struct SingleListOp *target) // 删除尾节点
{
    struct SingleList *Node = target->end;
    if (Node != NULL)
    {
        struct SingleList *last = GetNode(target, (GetSize(target) - 1));
        if (last != NULL)
            if (DeletNode(last, Node))
            {
                target->end = last;
                target->size--;
                return 1;
            }
            else
                return 0;
        else
            return 0;
    }
    else
        return 0;
}

int Linked(struct SingleListOp *target, int locate) // 将尾节点与指定节点连接
{
    int Size = GetSize(target);
    struct SingleList *Node = GetNode(target, locate);
    target->end->next = Node;
    if (Node != NULL)
        return 1;
    else
        return 0;
}

int *SearchLocate(struct SingleListOp *target, char *Data) // 根据数据搜索节点所在位置
{
    int Size = GetSize(target), *num = (int *)malloc(Size * sizeof(int));
    int cnt = 0;
    struct SingleList *answer = NULL, *temp = target->head->next;
    for (size_t i = 1; i <= Size; i++)
    {
        num[i - 1] = 0;
        if (!strcmp(Data, temp->Data))
        {
            answer = temp;
            num[cnt] = i;
            cnt++;
        }
    }
    return num;
}

struct SingleListOp *CreatSingleList(char *Name) // 创建新链表
{
    struct SingleListOp *HeadNode = NULL;
    HeadNode = (struct SingleListOp *)malloc(sizeof(struct SingleListOp));
    if (HeadNode != NULL)
    {
        HeadNode->head = CreatHead(Name);
        if (HeadNode->head != NULL)
        {
            HeadNode->end = HeadNode->head;
            HeadNode->size = 0;
        }
    }
    return HeadNode;
}

struct SingleList *InsertNode(struct SingleListOp *target, int cnt, char *Data) // 任意位置插入节点
{
    struct SingleList *temp = NULL;
    if (cnt == (GetSize(target) + 1))
        temp = AddFromEnd(target, Data);
    else if (cnt == 1)
        temp = AddFromHead(target, Data);
    else
    {
        struct SingleList *last = GetNode(target, cnt - 1);
        if (last != NULL)
        {
            temp = AddNode(Data, last);
            if (temp != NULL)
                target->size++;
        }
    }
    return temp;
}

int DelNode(int locate, struct SingleListOp *target) // 删除指定位置的节点
{
    if (locate == GetSize(target))
        return DelFromEnd(target);
    else
    {
        struct SingleList *Node = GetNode(target, locate);
        if (Node != NULL)
        {
            struct SingleList *last = GetNode(target, locate - 1);
            if (last != NULL)
                if (DeletNode(last, Node))
                {
                    target->size--;
                    return 1;
                }
                else
                    return 0;
            else
                return 0;
        }
        else
            return 0;
    }
}

int ChangeNode(int cnt, struct SingleListOp *target, char *Data) // 更改指定节点数据
{
    struct SingleList *Node = GetNode(target, cnt);
    if (Node != NULL)
    {
        ChangeData(Data, Node);
        return 1;
    }
    else
        return 0;
}

int CleanList(struct SingleListOp *target) // 清空链表
{
    struct SingleList *head = target->head;
    struct SingleList *temp = head->next;
    int cnt = GetSize(target);
    target->end->next = NULL;
    for (size_t i = 0; i < cnt; i++)
    {
        struct SingleList *next = temp->next;
        DeletNode(head, temp);
        temp = next;
    }
    free(head);
    head = NULL;
    temp = NULL;
    target->head = NULL;
    target->end = NULL;
    target->size = 0;
    target = NULL;
    if (target == NULL)
        return 1;
    else
        return 0;
}

int isCircle(struct SingleListOp *target) // 判断是否成环
{
    int Size = GetSize(target);
    struct SingleList *Node = target->head;
    int answer = 0, cnt = 0;
    while (Node->next != NULL)
    {
        Node = Node->next;
        cnt++;
        if (cnt > Size)
        {
            answer = 1;
            break;
        }
    }
    return answer;
}

int ParitySwapping(struct SingleListOp *target) // 奇偶对换
{
    struct SingleList *Node = target->head->next, *last = target->head;
    int Size = GetSize(target);
    for (int cnt = 1; cnt < Size; cnt += 2)
    {
        if (Node->next == target->end)
            target->end = Node;
        swap(Node, Node->next, last);
        last = Node;
        Node = Node->next;
    }
    return 1;
}

struct SingleList *GetMiddle(struct SingleListOp *target) // 取中间值
{
    int Middle = GetSize(target) / 2;
    struct SingleList *Node = GetNode(target, Middle);
    return Node;
}

int Reversal(struct SingleListOp *target) // 非递归反转链表
{
    struct SingleList *Node = target->head->next, *last = target->head;
    if (Node != target->head && Node != NULL)
    {
        int Size = GetSize(target);
        for (int i = 1; i < Size; i++)
        {
            Node = target->head->next;
            last = target->head;
            for (int i1 = 1; i1 <= Size - i; i1++)
            {
                swap(Node, Node->next, last);
                last = last->next;
            }
        }
        target->end = GetNode(target, Size);
        return 1;
    }
    else
        return 0;
}

int recursionReveral(struct SingleListOp *target, int cnt, int Size) // 递归反转链表
{
    struct SingleList *First = GetNode(target, cnt), *Second = GetNode(target, Size + 1 - cnt);
    struct SingleList *Flast = NULL, *Fnext = First->next, *Slast = GetNode(target, Size - cnt), *Snext = Second->next;
    if (cnt == 1)
        Flast = target->head;
    else
        Flast = GetNode(target, cnt-1);
    Slast->next = First;
    Flast->next = Second;
    First->next = Snext;
    Second->next = Fnext;
    cnt++;
    if (cnt <= (Size / 2))
        recursionReveral(target, cnt, Size);
    return 1;
}