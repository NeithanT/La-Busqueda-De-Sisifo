#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Heap.h"
#include <ctype.h>

struct Heap* create_heap(int capacity) {

    struct Heap* heap = (struct Heap*)calloc(1, sizeof(struct Heap));
    if (heap == NULL) {
        return NULL;
    }

    heap->texts = (struct Text**)calloc(capacity, sizeof(struct Text*));
    if (heap->texts == NULL) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

/* swap for primitive ints is not used - heap stores Text* now */

// Swap for Text pointers
void swap(struct Text** a, struct Text** b) {
    struct Text* tmp = *a;
    *a = *b;
    *b = tmp;
}

struct Text* delete_min(struct Heap* heap) {
    if (!heap || heap->size == 0) return NULL;

    struct Text* min = heap->texts[0];
    heap->texts[0] = heap->texts[--heap->size];

    // heapify down
    int idx = 0;
    while (1) {
        int l = left_child(idx);
        int r = right_child(idx);
        int smallest = idx;
        if (l < heap->size && heap->texts[l]->year < heap->texts[smallest]->year) smallest = l;
        if (r < heap->size && heap->texts[r]->year < heap->texts[smallest]->year) smallest = r;
        if (smallest == idx) break;
        swap(&heap->texts[idx], &heap->texts[smallest]);
        idx = smallest;
    }

    return min;
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

int is_full(struct Heap* heap) {
    return heap->size >= heap->capacity;
}

int is_empty(struct Heap* heap) {
    return heap->size == 0;
}

int insert(struct Heap* heap, struct Text* value) {

    if (heap == NULL) {
        return -1;
    }


    if (is_full(heap)) {
        printf("Heap lleno\n");
        return -1;
    }

    // insertar al final
    int idx = heap->size++;
    heap->texts[idx] = value;

    // heapify up (min-heap basado en 'year')
    while (idx > 0 && heap->texts[parent(idx)]->year > heap->texts[idx]->year) {
        swap(&heap->texts[parent(idx)], &heap->texts[idx]);
        idx = parent(idx);
    }

    return 0;
}

int free_heap(struct Heap* heap) {

    if (heap == NULL) {
        return -1;
    }

    if (heap->texts) {
        
        for (int i = 0; i < heap->size; ++i) {
            if (heap->texts[i]) {
                free(heap->texts[i]->author_name);
                free(heap->texts[i]->author_last_names);
                free(heap->texts[i]->title);
                free(heap->texts[i]->ruta_relativa);
                free(heap->texts[i]->abstract);
                free(heap->texts[i]);
            }
        }
        free(heap->texts);
    }
    free(heap);

    return 0;
}

struct Text* read_line(FILE *fp) {

    if (fp == NULL) return NULL;

    struct Text* text = (struct Text*)calloc(1, sizeof(struct Text));
    if (!text) return NULL;

    //TODO esta vaina
    return text;
}