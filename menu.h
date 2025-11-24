#ifndef MENU_H
#define MENU_H

#include "Sort.h"

int print_intro();

int show_menu();

int identify_choice(char c, struct Text* txt);

void sort_by_title(struct Text* txt);

void sort_by_year(struct Text* txt);

void sort_by_word_size(struct Text* txt);

void sort_by_filename(struct Text* txt);

void sort_by_palindromes(struct Text* txt);

#endif //MENU_H