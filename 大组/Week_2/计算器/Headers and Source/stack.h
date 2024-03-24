#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef Stack_H
#define Stack_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
// ջ�ṹ��
struct Stack {
    char stackName[20];
    struct node* HeadNode;
    size_t size;
};

// ��ʼ��һ������
struct Stack* initStack(char StackName[20]);

// ��ָ��ջ��ӽڵ�
int addNode(struct Stack* Stack, void* data);

// ����ͷ�ڵ�
void* getNode(struct Stack* Stack);

int changeData(struct Stack* Stack, void* Data);
// ���ջ
int cleanStack(struct Stack* Stack);

// ��ȡͷ�ڵ�����
void* getData(struct Stack* Stack);

#endif