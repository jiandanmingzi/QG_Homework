#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#define succeed 1
#define failed 0
#define Status int

typedef struct min_heap
{
    int *arr;
    int size;
    int capacity;
} min_heap;

min_heap *create_min_heap(int);

Status insert_min_heap(min_heap *, int);

Status delete_min_heap(min_heap *,int);

int search_min_heap(min_heap *, int);

Status print_min_heap(min_heap *);

#endif