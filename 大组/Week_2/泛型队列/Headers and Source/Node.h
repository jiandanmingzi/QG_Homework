#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef Node_H
#define Node_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    void* Data;        // ����ڵ�洢������
    struct node* next; // ָ����һ���ڵ��ָ��
};

// �����½ڵ�
struct node* CreatNode(void* data);

// ��ӽڵ�
struct node* AddNode(void* Data, struct node* last);

// ɾ���ڵ�
int DeletNode(struct node* last, struct node* Node);

// �޸Ľڵ�����
int ChangeData(void* Data, struct node* Node);

// �����ڵ�λ��
void swap(struct node* First, struct node* Second, struct node* FirstLast);

#endif