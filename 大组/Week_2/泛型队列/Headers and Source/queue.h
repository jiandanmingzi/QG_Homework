#pragma once
#ifndef Queue_H
#define Queue_H
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
struct Queue* initQueue(size_t capacity, char queueName[20]);

// ��ָ��������ӽڵ�
int addNode(struct Queue* queue, void* data);

// ����ͷ�ڵ�
void* getNode(struct Queue* queue);

int changeData(struct Queue* queue, void* Data);

// ��ն���
int cleanQueue(struct Queue* queue);

// ��ȡͷ�ڵ�����
void* getData(struct Queue* queue);

#endif