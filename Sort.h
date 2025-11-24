#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdio.h>
#include "Heap.h"
struct Text {
    
    struct HeapText* names ;
    struct HeapText* last_names;
    struct HeapText* titles;
    struct HeapText* routes;
    struct HeapYears* years;
    struct HeapText* abstracts;

};

int quick_sort();

int sort_by_name();

int sort_by_title_size();

struct Text* read_file();

char* read_line(FILE* fp);

void bubble_sort_text(struct HeapText* heap, int compare_type);

void bubble_sort_years(struct HeapYears* heap, struct HeapText* titles);

int should_swap_texts(const char* text1, const char* text2, int compare_type);

int count_words(const char* text);

int count_palindromes(const char* text);

int is_palindrome(const char* word);

void free_Text(struct Text* text);

void remove_delimiter(char* str, char delimiter);

#endif // SORT_H