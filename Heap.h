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

int parent(int index);

int leftChild(int index);

int rightChild(int index);

int insert(struct Heap* heap, int value);

int deleteMin(struct Heap* heap);

void swap(int* a, int* b);

int isFull(struct Heap* heap);

int freeHeap(struct Heap* heap);

#endif // HEAP_H