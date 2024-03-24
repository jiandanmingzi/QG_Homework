#pragma once
#ifndef Queue_H
#define Queue_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
// 泛型队列结构体
struct Queue
{
    char queueName[20];
    struct node* HeadNode;
    struct node* LastNode;
    size_t capacity;
    size_t size;
};

// 初始化一条队列
struct Queue* initQueue(size_t capacity, char queueName[20]);

// 给指定队列添加节点
int addNode(struct Queue* queue, void* data);

// 弹出头节点
void* getNode(struct Queue* queue);

int changeData(struct Queue* queue, void* Data);

// 清空队列
int cleanQueue(struct Queue* queue);

// 获取头节点数据
void* getData(struct Queue* queue);

#endif