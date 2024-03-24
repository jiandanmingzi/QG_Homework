#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef Stack_H
#define Stack_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
// 栈结构体
struct Stack {
    char stackName[20];
    struct node* HeadNode;
    size_t size;
};

// 初始化一条队列
struct Stack* initStack(char StackName[20]);

// 给指定栈添加节点
int addNode(struct Stack* Stack, void* data);

// 弹出头节点
void* getNode(struct Stack* Stack);

int changeData(struct Stack* Stack, void* Data);
// 清空栈
int cleanStack(struct Stack* Stack);

// 获取头节点数据
void* getData(struct Stack* Stack);

#endif