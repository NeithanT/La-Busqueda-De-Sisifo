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
 * Devuelve el index del hijo derecho en un arbol heap
 * Entrada: index i
 * Devuelve: el hijo derecho
 */
int right_child(int index) {
    return 2 * index + 2;
}

// Funciones del heap para textos

/**
 * Funcion que hace calloc para un TextHeap
 * Entrada:
 *  capacity: entero que dice la capacidad del heao
 * Salida:
 *  HeapText* : el nuevo HeapText creado
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

/**
 * Inserta texto a un heap, como un heap, en el ultimo posicion
 */
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

/**
 * Elimina y devuelve el texto minimo del heap
 * Entradas:
 *  heap: puntero al HeapText
 * Salidas:
 *  char*: el texto en [0], o NULL si esta vacio
 */
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

/**
 * Verifica si el heap de textos esta lleno
 * Entradas:
 *  heap: puntero al heap
 * Salidas:
 *  int: 1 si esta lleno, 0 si no
 */
int is_full_text(struct HeapText* heap) {
    return heap->size >= heap->capacity;
}

/**
 * checkea si el heap de textos esta vacio
 * Entradas:
 *  heap: puntero al heao
 * Salidas:
 *  int: 1 si esta vacio(size 0), 0 si no
 */
int is_empty_text(struct HeapText* heap) {
    return heap->size == 0;
}

/**
 * hace free ...
 * Entradas:
 *  heap: puntero al heap
 * Salidas:
 *  int: 0 exito, -1 error
 */
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

/**
 * Crea un nuevo heap para years
 * Entradas:
 *  capacity: capacidad del heap
 * Salidas:
 *  HeapYears*: puntero al nuevo heap, o NULL si fue error
 */
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

/**
 * Intercambia dos valores enteros
 * Entradas:
 *  a: puntero al primer int
 *  b: puntero al segundo int
 * Salidas:
 *  no
 */
void swap_years(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * Inserta un tiempo/a;o en el heap
 * Entradas:
 *  heap: puntero al heap
 *  value: el valor a insertar
 * Salidas:
 *  int: 0 si fue exito, -1 error
 */
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

/**
 * Elimina y devuelve el [0] del heap
 * Entradas:
 *  heap: puntero al heap
 * Salidas:
 *  int: el valor en [0], -1 si error
 */
int delete_min_years(struct HeapYears* heap) {
    if (heap == NULL || is_empty_years(heap)) {
        return -1;
    }

    int min = heap->years[0];
    // TODO ordenar

    heap->size--;
    return min;
}

/**
 * Verifica si el heap de years esta lleno
 * Entradas:
 *  heap: puntero al heap
 * Salidas:
 *  int: 1 si lleno, 0 si no
 */
int is_full_years(struct HeapYears* heap) {
    return heap->size >= heap->capacity;
}

/**
 * Verifica si el heap de años esta vacio
 * Entradas:
 *  heap: puntero al HeapYears
 * Salidas:
 *  int: 1 si vacio, 0 si no
 */
int is_empty_years(struct HeapYears* heap) {
    return heap->size == 0;
}

/**
 * Libera la memoria del heap de years
 * Entradas:
 *  heap: puntero al heap
 * Salidas:
 *  int: 0 si exito, -1 si error
 */
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
