#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "Sort.h"

#define INTRO "menu.txt"


int print_intro() {

    FILE *file = fopen(INTRO, "r");

    if (file == NULL) {return -1;}

    char buff[256];

    while (fgets(buff, 256, file)) {
        printf("%s", buff);
    }

    fclose(file);
    return 0;
}

int show_menu() {

    print_intro();
    struct Text* txt = read_file();

    char choice = 0;

    while (choice != '6') {

        printf("\n\n");
        printf("\t\t 1 - Ordenador por Titulo de la publicacion \n");
        printf("\t\t 2 - Ordenador por Año de la publicacion \n");
        printf("\t\t 3 - Ordenador por tamano en palabras \n");
        printf("\t\t 4 - Ordenador por nombre del archivo \n");
        printf("\t\t 5 - Ordenador por cantidad de palindromos en el abstract \n");
        printf("\t\t 6 - Salir \n");
        printf("\t\t     Escoge una opcion:");

        scanf("%c", &choice);
        putchar('\n');
        getchar();

        identify_choice(choice, txt);
    }

}

int identify_choice(char c, struct Text* txt) {

    switch (c)
    {
    case '1':
        sort_by_title(txt);
        return 0;
    case '2':
        sort_by_year(txt);
        return 0;
    case '3':
        sort_by_word_size(txt);
        return 0;
    case '4':
        sort_by_filename(txt);
        return 0;
    case '5':
        sort_by_palindromes(txt);
        return 0;
    case '6':
        return 0;
    default:
        printf("\t\tOpcion Invalida, asegurese de no tener espacios :%c \n", c);
        return -1;
    }

    return 0;
}

void sort_by_title(struct Text* txt) {
    bubble_sort_text(txt->titles, 1);
    printf("\n\t\t------ Publicaciones Ordenadas por Titulo ------\n");
    for (int i = 0; i < txt->titles->size; i++) {
        printf("\t\t%d. %s\n", i + 1, txt->titles->texts[i]);
    }
}

void sort_by_year(struct Text* txt) {
    bubble_sort_years(txt->years, txt->titles);
    printf("\n\t\t--- Publicaciones Ordenadas por Año ---\n");
    for (int i = 0; i < txt->years->size; i++) {
        printf("\t\t%d. %d - %s\n", i + 1, txt->years->years[i], txt->titles->texts[i]);
    }
}

void sort_by_word_size(struct Text* txt) {
    bubble_sort_text(txt->titles, 3);
    printf("\n\t\t--- Publicaciones Ordenadas por Tamano en Palabras ---\n");
    for (int i = 0; i < txt->titles->size; i++) {
        printf("\t\t%d. %s (%d palabras)\n", i + 1, txt->titles->texts[i], count_words(txt->titles->texts[i]));
    }
}

void sort_by_filename(struct Text* txt) {
    bubble_sort_text(txt->routes, 4);
    printf("\n\t\t--- Publicaciones Ordenadas por Nombre del Archivo ---\n");
    for (int i = 0; i < txt->routes->size; i++) {
        printf("\t\t%d. %s\n", i + 1, txt->routes->texts[i]);
    }
}

void sort_by_palindromes(struct Text* txt) {
    bubble_sort_text(txt->abstracts, 5);
    printf("\n\t\t--- Publicaciones Ordenadas por Cantidad de Palindromos en el Abstract ---\n");
    for (int i = 0; i < txt->abstracts->size; i++) {
        printf("\t\t%d. Palindromos: %d\n", i + 1, count_palindromes(txt->abstracts->texts[i]));
        printf("\t\t    %s\n", txt->abstracts->texts[i]);
    }
}