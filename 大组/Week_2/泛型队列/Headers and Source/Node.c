#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    void* Data;       // ����ڵ�洢������
    struct node* next; // ָ����һ���ڵ��ָ��
};

// �����½ڵ�
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

// ��ӽڵ�
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

// ɾ���ڵ�
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

// �޸Ľڵ�����
int ChangeData(void* Data, struct node* Node)
{
    Node->Data = Data;
    if (Node->Data == Data)
        return 1;
    else
        return 0;
}

// �����ڵ�λ��
void swap(struct node* First, struct node* Second, struct node* FirstLast)
{
    struct node* temp = Second->next;
    FirstLast->next = Second;
    Second->next = First;
    First->next = temp;
}