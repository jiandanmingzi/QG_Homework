#ifndef SingleList_H
#define SingleList_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct SingleList;

struct SingleList *CreatHead(char *List_Name); // ����������

struct SingleList *AddNode(char *Data, struct SingleList *last); // ��ӽڵ�

int DeletNode(struct SingleList *last, struct SingleList *Node); // ɾ���ڵ�

int ChangeData(char *Data, struct SingleList *Node); // �޸Ľڵ�����

void swap(struct SingleList *First, struct SingleList *Second, struct SingleList *FirstLast); // �����ڵ�λ��