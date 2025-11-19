#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Heap.h"

struct heap* create_heap(int capacity) {

    struct heap* heap = (struct heap*)calloc(1, sizeof(struct heap));
    if (heap == NULL) {
        return NULL;
    }

    heap->array = (int*)calloc(capacity, sizeof(int));
    if (heap->array == NULL) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int index) {
    return floor((index - 1) / 2);
}

int left_child(int index) {
    return 2 * index + 1;
}

int right_child(int index) {
    return 2 * index + 2;
}

int is_full(struct heap* heap) {
    return heap->size >= heap->capacity;
}

int is_empty(struct heap* heap) {
    return heap->size == 0;
}

int insert(struct heap* heap, int value) {

    if (heap == NULL) {
        return -1;
    }

    if (is_full(heap)) {
        printf("Estamos cocinados\n");
        return -1;
    }

    heap->array[heap->size] = value;
    heap->size++;
    
    return 0;
}

int free_heap(struct heap* heap) {

    if (heap == NULL) {
        return -1;
    }

    free(heap->array);
    free(heap);

    return 0;
}