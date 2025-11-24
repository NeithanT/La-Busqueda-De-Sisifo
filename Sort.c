#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Sort.h"
#include "Heap.h"

#define ARCHIVOS "archivo.txt"
#define SIZE 70
#define BUFFER 256

/**
 * Lee una linea , hasta \n
 * Entrada: file: puntero al filedescriptor
 * Salida: char*: la linea leida o NULL si  error
 */
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

    // quitarme los espacios extras del +20 capacity
    char* final_buffer = realloc(buffer, length + 1);
    if (final_buffer != NULL) {
        buffer = final_buffer;
    }
    
    return buffer;
}

/**
 * divide un campo de una cadena por los | esos
 * Entrada: 
 *  current: puntero a un texto
 *  delimiter: caracter |
 * Salida: char*: el campo dividido
 */
char* end_field(char** current, char delimiter) {
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

/**
 * Remueve el delimitador al final de la cadena
 * Entrada: str: cadena, delimiter: caracter delimitador
 * Salida: ninguna
 */
void remove_delimiter(char* str, char delimiter) {
    if (str != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == delimiter) {
            str[len - 1] = '\0';
        }
    }
}

/**
 * Parsea una linea de publicacion en campos
 * Entrada: line: linea a parsear, fields: arreglo de campos, field_count: numero de campos
 * Salida: int: 1 si exito, 0 si error
 */
int divide_line(char* line, char** fields, int field_count) {
    if (line == NULL || fields == NULL) {
        return 0;
    }
    
    char* current = line;
    
    for (int i = 0; i < field_count; i++) {
        fields[i] = end_field(&current, '|');
        if (fields[i] == NULL) {
            return 0;
        }
    }
    
    remove_delimiter(fields[field_count - 1], '|');
    
    return 1;
}

/**
 * Agrega los datos de publicacion en la estructura Text
 * Entrada: text: puntero a la estructura Text
 * fields: arreglo de title, abstract, etc...
 */
void insert_data(struct Text* text, char** fields) {
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

/**
 * Crea la estructura Text
 * Entrada: ninguna
 * Salida: struct Text*
 */
struct Text* create_text_heaps() {
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

/**
 * Lee el archivo 
 * Entrada: ninguna
 * Salida: 
 * struct Text*: puntero a la estructura con datos
 * o NUll si error
 */
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
        
        if (divide_line(line, fields, 6)) {
            insert_data(text, fields);
        }

        free(line);
    }

    fclose(fp);

    return text;
}

/**
 * Extrae el nombre del archivo de una ruta, le quita el /repo/
 * Entrada: path: ruta del archivo
 * Salida: char*: nombre del archivo
 * 
 */
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

/**
 * implementar la comparacion a textos! el strcmp existe thanks god
 * Entrada: text1 y text2, textos de entrada
 * Salida: int: 1 si text1 > text2, 0 si no
 */
int compare_by_title(const char* text1, const char* text2) {
    // parametros constantes xq asi es los parametros de strcmp
    return strcmp(text1, text2) > 0;
}

/**
 * Compara dos textos por cantidad de palabras
 * Entrada: text1: primer texto, text2: segundo texto
 * Salida: int: 1 si text1 tiene mas palabras, 0 otherwise
 */
int compare_by_word_count(const char* text1, const char* text2) {
    return count_words(text1) > count_words(text2);
}

/**
 * Compara dos rutas por nombre de archivo
 * Entrada: path1: primera ruta, path2: segunda ruta
 * Salida: int: 1 si filename1 > filename2, 0 otherwise
 */
int compare_by_filename(const char* path1, const char* path2) {
    char* filename1 = extract_filename(path1);
    char* filename2 = extract_filename(path2);
    return strcmp(filename1, filename2) > 0;
}

/**
 * Compara dos textos por cantidad de palindromos
 * Entrada: text1: primer texto, text2: segundo texto
 * Salida: int: 1 si text1 tiene mas palindromos, 0 otherwise
 */
int compare_by_palindromes(const char* text1, const char* text2) {
    return count_palindromes(text1) > count_palindromes(text2);
}

/**
 * vaina que se tira dentro del bubble sort del heap
 * Entrada: text1: primer texto, text2: segundo texto, compare_type: tipo de comparacion, opcion del menu
 * Salida: int: 1 si se debe intercambiar, 0 otherwise
 */
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

/**
 * Ordena un heap de textos usando bubble sort! xq un heap asi lo defini
 * Entrada: heap: puntero al heap, compare_type: tipo de comparacion, opcion del main...
 * Salida: ninguna
 */
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

/**
 * Ordena un heap de tiempo, ajusta los titulos tmb
 * Entrada: heap: puntero al heap de años, titles: puntero al heap de titulos
 * Salida: ninguna
 */
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

/**
 * Cuenta el numero de palabras en un texto
 * Entrada:
 *  text: texto a contar
 * Salida: int: numero de palabras
 */
int count_words(const char* text) {
    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    int word_count = 1;
    // se podria hacer por strtok??? seguro si
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n')
            word_count++;
    }

    return word_count;
}

/**
 * Verifica si una palabra es palindromo
 * Entrada: word: palabra a verificar
 * Salida: int: 1 si es palindromo, 0 si no
 */
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

/**
 * Cuenta el numero de palindromos en un texto
 * Entrada: text: texto a analizar
 * Salida: int: numero de palindromos
 */
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

/**
 * Libera la memoria de la estructura Text
 * Entrada: text: puntero a Text
 * Salida: ninguna
 */
void free_Text(struct Text* text) {
    if (text == NULL) return;

    free_heap_text(text->names);
    free_heap_text(text->last_names);
    free_heap_text(text->titles);
    free_heap_text(text->routes);
    free_heap_years(text->years);
    free_heap_text(text->abstracts);
    
    free(text);
}