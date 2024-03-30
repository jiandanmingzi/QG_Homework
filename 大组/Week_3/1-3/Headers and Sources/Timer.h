#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef TIMER_H
#define TIMER_H
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
int GetTime(void (*sort)(int*, int), int* arr, int n);
int SingleDataTest(void (*sort)(int*, int), int n);
int MultipleDataTest(void (*sort)(int*, int), int n, int times);
#endif