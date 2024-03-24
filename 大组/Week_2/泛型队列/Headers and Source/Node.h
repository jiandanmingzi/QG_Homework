#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef Node_H
#define Node_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    void* Data;        // 链表节点存储的数据
    struct node* next; // 指向下一个节点的指针
};

// 创建新节点
struct node* CreatNode(void* data);

// 添加节点
struct node* AddNode(void* Data, struct node* last);

// 删除节点
int DeletNode(struct node* last, struct node* Node);

// 修改节点数据
int ChangeData(void* Data, struct node* Node);

// 交换节点位置
void swap(struct node* First, struct node* Second, struct node* FirstLast);

#endif