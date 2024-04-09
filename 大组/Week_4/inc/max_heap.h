#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#define succeed 1
#define failed 0
#define Status int

typedef struct max_heap {
    int *arr;
    int size;
    int capacity;
} max_heap;

max_heap *create_max_heap(int );

Status insert_max_heap(max_heap *, int );

Status delete_max_heap(max_heap *,int);

int search_max_heap(max_heap *, int );

Status print_max_heap(max_heap *);

#endif