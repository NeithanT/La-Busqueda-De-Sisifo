#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
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

#endif // SORT_H