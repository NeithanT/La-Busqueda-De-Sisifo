#ifndef HEAP_H
#define HEAP_H


// La propia estructura de Heap, es una lista en esteroides
// Es un Min Heap
struct heap {

    int* array;
    int size;
    int capacity;

};

struct heap* create_heap(int capacity);

int parent(int index);

int left_child(int index);

int right_child(int index);

int insert(struct heap* heap, int value);

int delete_min(struct heap* heap);

void swap(int* a, int* b);

int is_full(struct heap* heap);

int free_heap(struct heap* heap);

#endif // HEAP_H