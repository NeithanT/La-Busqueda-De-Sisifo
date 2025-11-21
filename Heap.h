#ifndef HEAP_H
#define HEAP_H

// La estructura de un archivo

struct Text {

    char* author_name;
    char* author_last_names;
    char* title;
    char* ruta_relativa;
    int year;
    char* abstract;
};

// La propia estructura de Heap, es una lista en esteroides
// Es un Min Heap
struct Heap {

    struct Text** texts;
    int size;
    int capacity;

};

struct Heap* create_heap(int capacity);

int parent(int index);

int left_child(int index);

int right_child(int index);

int is_empty(struct Heap* heap);

int insert(struct Heap* heap, struct Text* value);

struct Text* delete_min(struct Heap* heap);

void swap(struct Text** a, struct Text** b);

int is_full(struct Heap* heap);

int free_heap(struct Heap* heap);

struct Text* read_line(FILE *fp);

struct Heap* read_file();

#endif // HEAP_H