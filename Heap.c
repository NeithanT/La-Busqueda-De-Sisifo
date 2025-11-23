#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Heap.h"

// Funciones generales de Heap

/**
 * Devuelve el index del padre directo en un arbol heap
 * Entrada: index i
 * Devuelve: el padre en el arbol
 */
int parent(int index) {
    return floor((index - 1) / 2);
}

/**
 * Devuelve el index del hijo izquierdo en un arbol heap
 * Entrada: index i
 * Devuelve: el hijo izquierdo en el arbol
 */
int left_child(int index) {
    return 2 * index + 1;
}

/**
 * Devuelve el index de una raiz en un arbol heap
 * Entrada: index i
 * Devuelve: el hijo derecho
 */
int right_child(int index) {
    return 2 * index + 2;
}

// Funciones del heap para textos

/**
 * 
 * 
 */
struct HeapText* create_heap_text(int capacity) {

    struct HeapText* heap = (struct HeapText*)calloc(1, sizeof(struct HeapText));
    if (heap == NULL) {
        return NULL;
    }

    heap->texts = (char**)calloc(capacity, sizeof(char*));
    if (heap->texts == NULL) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

/**
 * Intercambia el puntero de dos textos
 * funcion chivisima xq cambia los punteors
 * Entradas:
 *  char**a, puntero al char* osea al texto
 *  char**b, puntero al char*, eso
 * Salidas:
 *  no
 */
void swap_text(char** a, char** b) {
    char* tmp = *a;
    *a = *b;
    *b = tmp;
}

int insert_text(struct HeapText* heap, char* value) {
    if (heap == NULL || value == NULL) {
        return -1;
    }

    if (is_full_text(heap)) {
        printf("HeapText lleno\n");
        return -1;
    }

    heap->texts[heap->size++] = value;

    return 0;
}

char* delete_min_text(struct HeapText* heap) {
    if (heap == NULL || is_empty_text(heap)) {
        return NULL;
    }

    char* min = heap->texts[0];
    heap->texts[0] = NULL;

    // TODO reordenar arbol
    heap->size--;
    return min;
}

int is_full_text(struct HeapText* heap) {
    return heap->size >= heap->capacity;
}

int is_empty_text(struct HeapText* heap) {
    return heap->size == 0;
}

int free_heap_text(struct HeapText* heap) {
    if (heap == NULL) {
        return -1;
    }

    if (heap->texts) {
        for (int i = 0; i < heap->size; ++i) {
            if (heap->texts[i]) {
                free(heap->texts[i]);
            }
        }
        free(heap->texts);
    }
    free(heap);
    return 0;
}

// Funciones de heap para enteros/years/a;os en este caso

struct HeapYears* create_heap_years(int capacity) {

    struct HeapYears* heap = (struct HeapYears*)calloc(1, sizeof(struct HeapYears));
    if (heap == NULL) {
        return NULL;
    }

    heap->years = (int*)calloc(capacity, sizeof(int));
    if (heap->years == NULL) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap_years(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int insert_years(struct HeapYears* heap, int value) {

    if (heap == NULL) {
        return -1;
    }

    if (is_full_years(heap)) {
        printf("HeapYears lleno\n");
        return -1;
    }

    heap->years[heap->size++] = value;
    return 0;
}

int delete_min_years(struct HeapYears* heap) {
    if (heap == NULL || is_empty_years(heap)) {
        return -1;
    }

    int min = heap->years[0];
    // TODO ordenar

    heap->size--;
    return min;
}

int is_full_years(struct HeapYears* heap) {
    return heap->size >= heap->capacity;
}

int is_empty_years(struct HeapYears* heap) {
    return heap->size == 0;
}

int free_heap_years(struct HeapYears* heap) {
    if (heap == NULL) {
        return -1;
    }

    if (heap->years) {
        free(heap->years);
    }
    free(heap);
    return 0;
}
