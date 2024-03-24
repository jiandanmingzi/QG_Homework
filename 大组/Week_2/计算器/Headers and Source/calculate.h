#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef Calculate_H
#define Calculate_H
#include "stack.h"
#include <math.h>

// 数字结构体
struct NUM
{
    char INTEGER[11];
    char DECIMAL[11];
    char IntegerNum;
    char DecimalNum;
};

// 初始化并获取一个数字结构体
struct NUM* InitNum();

void addInt(struct NUM* Num, char num);

void addDec(struct NUM* Num, char num);

// 获取数字大小
double GetNum(struct NUM* Num);

// 执行计算
double GetAnswer(double firstNum, double secondNum, char c);

// 判断是否为操作符
int isOperator(char c);

// 判断是否为数字
int isNum(char c);

// 获取操作符优先级
int precedence(char op);

#endif