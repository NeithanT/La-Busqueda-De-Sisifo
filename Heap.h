#ifndef HEAP_H
#define HEAP_H

// Heap para los textos de autor, titulo, etc
struct HeapText {
    char** texts;
    int size;
    int capacity;
};

// Heap para enteros, en este caso los a;os
struct HeapYears {
    int* years;
    int size;
    int capacity;
};

// Funciones generales
int parent(int index);
int left_child(int index);
int right_child(int index);

// Funciones para textos

struct HeapText* create_heap_text(int capacity);

int insert_text(struct HeapText* heap, char* value);

char* delete_min_text(struct HeapText* heap);

void swap_text(char** a, char** b);

int is_full_text(struct HeapText* heap);

int is_empty_text(struct HeapText* heap);

int free_heap_text(struct HeapText* heap);

// Funciones para a;os years
struct HeapYears* create_heap_years(int capacity);

int insert_years(struct HeapYears* heap, int value);

int delete_min_years(struct HeapYears* heap);

void swap_years(int* a, int* b);

int is_full_years(struct HeapYears* heap);

int is_empty_years(struct HeapYears* heap);

int free_heap_years(struct HeapYears* heap);

#endif // HEAP_H