#ifndef HEAP_H
#define HEAP_H


// La propia estructura de Heap, es una lista en esteroides
// Es un Min Heap
struct Heap {

    int* array;
    int size;
    int capacity;

};

struct Heap* createHeap(int capacity);
void insert(struct Heap* heap, int value);
int deleteMin(struct Heap* heap);
int peekMin(struct Heap* heap);
void heapifyUp(struct Heap* heap, int index);
void heapifyDown(struct Heap* heap, int index);
void swap(int* a, int* b);
int isEmpty(struct Heap* heap);
int isFull(struct Heap* heap);


#endif // HEAP_H