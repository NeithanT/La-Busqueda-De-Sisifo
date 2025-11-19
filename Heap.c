#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Heap.h"

struct Heap* createHeap(int capacity) {

    struct Heap* heap = (struct Heap*)calloc(1, sizeof(struct Heap));
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

int leftChild(int index) {
    return 2 * index + 1;
}

int rightChild(int index) {
    return 2 * index + 2;
}

int isFull(struct Heap* heap) {
    return heap->size >= heap->capacity;
}

int insert(struct Heap* heap, int value) {

    if (heap == NULL) {
        return -1;
    }

    if (isFull(heap)) {
        printf("Estamos cocinados\n");
        return;
    }

    heap->array[heap->size] = value;
    heap->size++;
}

int deleteMin(struct Heap* heap) {
    if (isEmpty(heap)) {
        printf("Heap is empty\n");
        return -1;
    }
    int min = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return min;
}

int freeHeap(struct Heap* heap) {

    if (heap == NULL) {
        return -1;
    }

    free(heap->array);
    free(heap);

    return 0;
}