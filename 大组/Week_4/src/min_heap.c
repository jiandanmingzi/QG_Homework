#include<stdio.h>
#include<stdlib.h>
#include"min_heap.h"

min_heap *create_min_heap(int capacity)
{
    min_heap *heap = (min_heap *)malloc(sizeof(min_heap));
    if (heap == NULL)
        return NULL;
    heap->arr = (int *)malloc(capacity * sizeof(int));
    if (heap->arr == NULL)
        return NULL;
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

Status insert_min_heap(min_heap *heap, int value)
{
    if (heap->size == heap->capacity)
    {
        printf("Heap is full\n");
        return failed;
    }
    heap->size++;
    int i = heap->size - 1;
    heap->arr[i] = value;
    while (i != 0 && heap->arr[(i - 1) / 2] > heap->arr[i])
    {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[(i - 1) / 2];
        heap->arr[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    return succeed;
}

Status delete_min_heap(min_heap *heap,int value)
{
    int i = search_min_heap(heap,value);
    if(i == -1)
    {
        printf("Element not found\n");
        return failed;
    }
    heap->arr[i] = heap->arr[heap->size - 1];
    heap->size--;
    while(i < heap->size)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if(left < heap->size && heap->arr[left] < heap->arr[smallest])
            smallest = left;
        if(right < heap->size && heap->arr[right] < heap->arr[smallest])
            smallest = right;
        if(smallest == i)
            break;
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[smallest];
        heap->arr[smallest] = temp;
        i = smallest;
    }
    return succeed;
}

int search_min_heap(min_heap *heap, int value)
{
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->arr[i] == value)
            return i;
    }
    return -1;
}

Status print_min_heap(min_heap *heap)
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