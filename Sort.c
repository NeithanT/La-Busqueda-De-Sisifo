#include <stdio.h>
#include <string.h>
#include "Sort.h"
#include "Heap.h"

#define ARCHIVOS "publicaciones.txt"
#define SIZE 70
#define BUFFER 256

char* read_line(FILE* file) {
    if (file == NULL) {
        return NULL;
    }
    
    size_t capacity = 2;
    size_t length = 0;
    char* buffer = (char*)calloc(capacity, sizeof(char));
    
    if (buffer == NULL) {
        return NULL;
    }
    
    int ch; // un entero xq fgetc devuelve un entero
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        
        // +1 xq funciona por index
        if (length + 1 >= capacity) {
            capacity += 20;
            char* new_buffer = realloc(buffer, capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        
        buffer[length++] = (char)ch;
    }
    
    buffer[length] = '\0';
    if (length == 0 && feof(file)) {
        free(buffer);
        return NULL;
    }
    
    char* final_buffer = realloc(buffer, length + 1);
    if (final_buffer != NULL) {
        buffer = final_buffer;
    }
    
    return buffer;
}

struct Text* read_file() {

    FILE *fp = fopen(ARCHIVOS, "r");

    if (fp == NULL) {
        return NULL;
    }

    struct Text* text = (struct Text*)calloc(1, sizeof(struct Text));
    if (text == NULL) {
        fclose(fp);
        return NULL;
    }

    text->names = create_heap_text(SIZE);
    text->last_names = create_heap_text(SIZE);
    text->titles = create_heap_text(SIZE);
    text->routes = create_heap_text(SIZE);
    text->years = create_heap_years(SIZE);
    text->abstracts = create_heap_text(SIZE);

    char* line;
    while ((line = read_line(fp)) != NULL) {

        char* name = strtok(line, "|");
        char* last_name = strtok(NULL, "|");
        char* title = strtok(NULL, "|");
        char* route = strtok(NULL, "|");
        char* year_str = strtok(NULL, "|");
        char* abstract = strtok(NULL, "|");

        
        if (name) insert_text(text->names, name);
        if (last_name) insert_text(text->last_names, last_name);
        if (title) insert_text(text->titles, title);
        if (route) insert_text(text->routes, route);
        if (year_str) {
            int year = atoi(year_str);
            insert_years(text->years, year);
        }
            if (abstract) insert_text(text->abstracts, abstract);

        free(line);
    }

    fclose(fp);

    return text;
}