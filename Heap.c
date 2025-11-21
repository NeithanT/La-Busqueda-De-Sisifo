#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Heap.h"
#include <ctype.h>

#define ARCHIVOS "archivo.txt"

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


/**
 * Funcion para agregar un elemento al heap
 * Entradas:
 *  heap: el heap al que se desea agregar el elemento
 *  value: el valor a agregar al heap
 * Salidas:
 * -1: En caso de error como nulls
 *  0: En caso de exito
 */
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

int free_text(struct Text* txt) {

    if (txt == NULL) {
        return -1;
    }

    free(txt->author_name);
    free(txt->author_last_names);
    free(txt->title);
    free(txt->ruta_relativa);
    free(txt->abstract);
    free(txt);
}

int free_heap(struct Heap* heap) {

    if (heap == NULL) {
        return -1;
    }

    if (heap->texts) {
        
        for (int i = 0; i < heap->size; ++i) {
            if (heap->texts[i]) {
                free_text(heap->texts[i]);
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

struct Heap* read_file() {

    FILE *fp = fopen(ARCHIVOS, "r");

    if (!fp) {
        return NULL;
    }

    char buffer[256];

    fread(buffer, sizeof(char), 256, fp);

    int index = 0;
}