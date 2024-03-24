#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef Calculate_H
#define Calculate_H
#include "stack.h"
#include <math.h>

// ���ֽṹ��
struct NUM
{
    char INTEGER[11];
    char DECIMAL[11];
    char IntegerNum;
    char DecimalNum;
};

// ��ʼ������ȡһ�����ֽṹ��
struct NUM* InitNum();

void addInt(struct NUM* Num, char num);

void addDec(struct NUM* Num, char num);

// ��ȡ���ִ�С
double GetNum(struct NUM* Num);

// ִ�м���
double GetAnswer(double firstNum, double secondNum, char c);

// �ж��Ƿ�Ϊ������
int isOperator(char c);

// �ж��Ƿ�Ϊ����
int isNum(char c);

// ��ȡ���������ȼ�
int precedence(char op);

#endif