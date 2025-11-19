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

void swap(struct Text** a, struct Text** b) {
    struct Text* tmp = *a;
    *a = *b;
    *b = tmp;
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

    heap->texts[heap->size++] = value;

    return 0;
}

int free_heap(struct Heap* heap) {

    if (heap == NULL) {
        return -1;
    }

    if (heap->texts) {
        
        // TODO, esto deberia ser un free text
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