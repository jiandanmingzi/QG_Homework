#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct DoubleList
{
};

struct DoubleList *CreatHead(char List_Name[]); // ����������

struct DoubleList *AddNode(char Data[], struct DoubleList *last); // ��ӽڵ�

int DeletNode(struct DoubleList *Node); // ɾ���ڵ�

int ChangeData(char *Data, struct DoubleList *Node); // �޸Ľڵ�����

void swap(struct DoubleList *First, struct DoubleList *Second); // �����ڵ�λ��
