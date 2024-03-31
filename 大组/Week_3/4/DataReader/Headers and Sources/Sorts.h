#pragma once
#ifndef SORT_H
#define SORT_H
void BubbleSort(int* arr, int n);
void CountSort(int* arr, int n);
void InsertSort(int* arr, int n);
void MergeSort(int* arr, int n);
void RQuickSort(int* arr, int n);
void NonRecirsopmQuickSort(int* arr, int n);
void RadixSort(int* arr, int n);
struct Sort
{
    char* name;
    void (*sort)(int*, int);
};
#endif