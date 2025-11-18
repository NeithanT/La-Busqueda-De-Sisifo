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

int parent(int i) {
    return floor((i - 1) / 2);
}

int leftChild(int i) {
    return 2 * i + 1;
}

int rightChild(int i) {
    return 2 * i + 2;
}

void heapifyUp(struct Heap* heap, int index) {
    while (index > 0 && heap->array[parent(index)] > heap->array[index]) {
        swap(&heap->array[parent(index)], &heap->array[index]);
        index = parent(index);
    }
}

void heapifyDown(struct Heap* heap, int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    if (left < heap->size && heap->array[left] < heap->array[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->array[right] < heap->array[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap->array[index], &heap->array[smallest]);
        heapifyDown(heap, smallest);
    }
}

int isEmpty(struct Heap* heap) {
    return heap->size == 0;
}

int isFull(struct Heap* heap) {
    return heap->size == heap->capacity;
}

void insert(struct Heap* heap, int value) {
    if (isFull(heap)) {
        printf("Heap is full\n");
        return;
    }
    heap->array[heap->size] = value;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
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

int peekMin(struct Heap* heap) {
    if (isEmpty(heap)) {
        printf("Heap is empty\n");
        return -1;
    }
    return heap->array[0];
}