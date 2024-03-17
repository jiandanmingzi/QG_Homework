#ifndef SingleLinkedList_H
#define SingleLinkedList_H
#include "SingleList.h"
struct SingleListOp;

int GetSize(struct SingleListOp *target); // ��ȡ������

struct SingleList *GetNode(struct SingleListOp *target, int cnt); // ��ȡ�ض�λ�õĽڵ�

struct SingleList *AddFromEnd(struct SingleListOp *target, char *Data); // ��β���

struct SingleList *AddFromHead(struct SingleListOp *target, char *Data); // ��ͷ���

int DelFromEnd(struct SingleListOp *target); // ɾ��β�ڵ�

int Linked(struct SingleListOp *target, int locate); // ��β�ڵ���ָ���ڵ�����

int *SearchLocate(struct SingleListOp *target, char *Data); // �������������ڵ�����λ��

struct SingleListOp *CreatSingleList(char *Name); // ����������

struct SingleList *InsertNode(struct SingleListOp *target, int cnt, char *Data); // ����λ�ò���ڵ�

int DelNode(int locate, struct SingleListOp *target); // ɾ��ָ��λ�õĽڵ�

int ChangeNode(int cnt, struct SingleListOp *target, char *Data); // ����ָ���ڵ�����

int CleanList(struct SingleListOp *target); // �������

int isCircle(struct SingleListOp *target); // �ж��Ƿ�ɻ�

int ParitySwapping(struct SingleListOp *target); // ��ż�Ի�

struct SingleList *GetMiddle(struct SingleListOp *target); // ȡ�м�ֵ
