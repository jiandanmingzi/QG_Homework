#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"

max_heap *create_max_heap(int capacity)
{
    max_heap *heap = (max_heap *)malloc(sizeof(max_heap));
    if (heap == NULL)
        return NULL;
    heap->arr = (int *)malloc(capacity * sizeof(int));
    if (heap->arr == NULL)
        return NULL;
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

Status insert_max_heap(max_heap *heap, int value)
{
    if (heap->size == heap->capacity)
    {
        printf("Heap is full\n");
        return failed;
    }
    heap->size++;
    int i = heap->size - 1;
    heap->arr[i] = value;
    while (i != 0 && heap->arr[(i - 1) / 2] < heap->arr[i])
    {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[(i - 1) / 2];
        heap->arr[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    return succeed;
}

Status delete_max_heap(max_heap *heap, int value)
{
    int i = search_max_heap(heap, value);
    if (i == -1)
    {
        printf("Element not found\n");
        return failed;
    }
    heap->arr[i] = heap->arr[heap->size - 1];
    heap->size--;
    while (i < heap->size)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < heap->size && heap->arr[left] > heap->arr[largest])
            largest = left;
        if (right < heap->size && heap->arr[right] > heap->arr[largest])
            largest = right;
        if (largest == i)
            break;
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[largest];
        heap->arr[largest] = temp;
        i = largest;
    }
    return succeed;
}

int search_max_heap(max_heap *heap, int value)
{
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->arr[i] == value)
            return i;
    }
    return -1;
}

Status print_max_heap(max_heap *heap)
{
    int flag = 1;
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d ", heap->arr[i]);
        if (i == 0 || i == 2 * flag - 1)
        {
            printf("\n");
            flag *= 2;
        }
    }
    printf("\n");
    return succeed;
}