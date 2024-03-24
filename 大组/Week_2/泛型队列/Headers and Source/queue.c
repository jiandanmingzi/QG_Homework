#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
// ���Ͷ��нṹ��
struct Queue
{
    char queueName[20];
    struct node* HeadNode;
    struct node* LastNode;
    size_t capacity;
    size_t size;
};

// ��ʼ��һ������
struct Queue* initQueue(size_t capacity, char queueName[20])
{
    struct Queue* queue = NULL;
    queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->HeadNode = NULL;
    queue->LastNode = NULL;
    strcpy(queue->queueName, queueName);
    return queue;
}

// ��ָ��������ӽڵ�
int addNode(struct Queue* queue, void* data)
{
    if (queue->capacity <= queue->size)
        return 0;
    struct node* Node = CreatNode(data);
    if (queue->size == 0)
        queue->HeadNode = Node;
    else
        queue->LastNode->next = Node;
    queue->LastNode = Node;
    Node->next = NULL;
    queue->size++;
    return 1;
}

// ����ͷ�ڵ�
void* getNode(struct Queue* queue)
{
    if (queue->size == 0)
        return NULL;
    struct node* Node = queue->HeadNode;
    queue->size--;
    queue->HeadNode = Node->next;
    void* data = Node->Data;
    Node->Data = NULL;
    Node->next = NULL;
    free(Node);
    return data;
}

int changeData(struct Queue* queue, void* Data)
{
    return ChangeData(Data, queue->HeadNode);
}

// ��ն���
int cleanQueue(struct Queue* queue)
{
    queue->LastNode = NULL;
    struct node* Next;
    if (queue->size != 0)
        for (struct node* Node = queue->HeadNode->next; (Node != NULL); Node = Next)
        {
            Next = Node->next;
            if (!DeletNode(queue->HeadNode, Node))
                return 0;
        }
    free(queue->HeadNode);
    queue->HeadNode = NULL;
    queue->size = 0;
    queue->capacity = 0;
    free(queue);
    queue = NULL;
    return 1;
}

// ��ȡͷ�ڵ�����
void* getData(struct Queue* queue)
{
    if (queue->size == 0)
        return NULL;
    return queue->HeadNode->Data;
}