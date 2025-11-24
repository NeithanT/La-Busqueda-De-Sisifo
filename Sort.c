#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Sort.h"
#include "Heap.h"

#define ARCHIVOS "archivo.txt"
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
        if (ch == '\r') {
            continue;
        }
        
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

char* parse_field(char** current, char delimiter) {
    if (current == NULL || *current == NULL) {
        return NULL;
    }
    
    char* field = *current;
    char* next_token = strchr(*current, delimiter);
    
    if (next_token) {
        *next_token = '\0';
        *current = next_token + 1;
    } else {
        *current = NULL;
    }
    
    return field;
}

void remove_trailing_delimiter(char* str, char delimiter) {
    if (str != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == delimiter) {
            str[len - 1] = '\0';
        }
    }
}

int parse_publication_line(char* line, char** fields, int field_count) {
    if (line == NULL || fields == NULL) {
        return 0;
    }
    
    char* current = line;
    
    for (int i = 0; i < field_count; i++) {
        fields[i] = parse_field(&current, '|');
        if (fields[i] == NULL) {
            return 0;
        }
    }
    
    remove_trailing_delimiter(fields[field_count - 1], '|');
    
    return 1;
}

void insert_publication_data(struct Text* text, char** fields) {
    if (text == NULL || fields == NULL) {
        return;
    }
    
    char* name = fields[0];
    char* last_name = fields[1];
    char* title = fields[2];
    char* route = fields[3];
    char* year_str = fields[4];
    char* abstract = fields[5];
    
    if (name && last_name && title && route && year_str && abstract) {
        insert_text(text->names, strdup(name));
        insert_text(text->last_names, strdup(last_name));
        insert_text(text->titles, strdup(title));
        insert_text(text->routes, strdup(route));
        insert_years(text->years, atoi(year_str));
        insert_text(text->abstracts, strdup(abstract));
    }
}

struct Text* create_text_heaps(void) {
    struct Text* text = (struct Text*)calloc(1, sizeof(struct Text));
    if (text == NULL) {
        return NULL;
    }

    text->names = create_heap_text(SIZE);
    text->last_names = create_heap_text(SIZE);
    text->titles = create_heap_text(SIZE);
    text->routes = create_heap_text(SIZE);
    text->years = create_heap_years(SIZE);
    text->abstracts = create_heap_text(SIZE);

    return text;
}

struct Text* read_file() {
    FILE *fp = fopen(ARCHIVOS, "r");

    if (fp == NULL) {
        return NULL;
    }

    struct Text* text = create_text_heaps();
    if (text == NULL) {
        fclose(fp);
        return NULL;
    }

    char* line;
    while ((line = read_line(fp)) != NULL) {
        char* fields[6];
        
        if (parse_publication_line(line, fields, 6)) {
            insert_publication_data(text, fields);
        }

        free(line);
    }

    fclose(fp);

    return text;
}


char* extract_filename(const char* path) {
    if (path == NULL) {
        return (char*)path;
    }
    
    char* filename = strrchr(path, '/');
    if (filename != NULL) {
        return filename + 1;
    }
    
    return (char*)path;
}


int compare_by_title(const char* text1, const char* text2) {
    return strcmp(text1, text2) > 0;
}


int compare_by_word_count(const char* text1, const char* text2) {
    return count_words(text1) > count_words(text2);
}

int compare_by_filename(const char* path1, const char* path2) {
    char* filename1 = extract_filename(path1);
    char* filename2 = extract_filename(path2);
    return strcmp(filename1, filename2) > 0;
}


int compare_by_palindromes(const char* text1, const char* text2) {
    return count_palindromes(text1) > count_palindromes(text2);
}

int should_swap_texts(const char* text1, const char* text2, int compare_type) {
    switch (compare_type) {
        case 1:
            return compare_by_title(text1, text2);
        case 3:
            return compare_by_word_count(text1, text2);
        case 4:
            return compare_by_filename(text1, text2);
        case 5:
            return compare_by_palindromes(text1, text2);
        default:
            return 0;
    }
}

void bubble_sort_text(struct HeapText* heap, int compare_type) {
    if (heap == NULL || heap->size <= 1) {
        return;
    }

    for (int i = 0; i < heap->size - 1; i++) {
        for (int j = 0; j < heap->size - i - 1; j++) {
            if (should_swap_texts(heap->texts[j], heap->texts[j + 1], compare_type)) {
                swap_text(&heap->texts[j], &heap->texts[j + 1]);
            }
        }
    }
}

void bubble_sort_years(struct HeapYears* heap, struct HeapText* titles) {
    if (heap == NULL || heap->size <= 1) {
        return;
    }

    for (int i = 0; i < heap->size - 1; i++) {
        for (int j = 0; j < heap->size - i - 1; j++) {
            if (heap->years[j] > heap->years[j + 1]) {
                swap_years(&heap->years[j], &heap->years[j + 1]);
                if (titles != NULL) {
                    swap_text(&titles->texts[j], &titles->texts[j + 1]);
                }
            }
        }
    }
}

int count_words(const char* text) {
    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    int word_count = 1;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n') {
            word_count++;
    }

    return word_count;
}

int is_palindrome(const char* word) {
    if (word == NULL || word[0] == '\0' || strlen(word) < 2) {
        return 0;
    }

    int len = strlen(word);
    int i = 0;
    int j = len - 1;

    for (int i = 0; i < len -1; i++) {
        if (tolower(word[i]) != tolower(word[j])) {
            return 0;
        }
        j--;
    }

    return 1;
}

int count_palindromes(const char* text) {
    if (text == NULL || text[0] == '\0' || strlen(text) < 2) {
        return 0;
    }

    int palindrome_count = 0;
    char* text_copy = (char*)calloc(strlen(text) + 1, sizeof(char));
    if (text_copy == NULL) {
        return 0;
    }
    
    strcpy(text_copy, text);

    char* word = strtok(text_copy, " \t\n");
    while (word != NULL) {
        if (is_palindrome(word)) {
            palindrome_count++;
        }
        word = strtok(NULL, " \t\n");
    }

    free(text_copy);
    return palindrome_count;
}