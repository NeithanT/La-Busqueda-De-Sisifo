#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

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

    char choice = 0;

    while (choice != '5') {

        printf("\n\n");
        printf("\t\t 1 - Ordenador por Titulo de la publicacion \n");
        printf("\t\t 2 - Ordenador por tamano en palabras \n");
        printf("\t\t 3 - Ordenador por nombre del archivo \n");
        printf("\t\t 4 - Ordenador por cantidad de palindromos en el abstract \n");
        printf("\t\t 5 - Salir \n");
        printf("\t\t     Escoge una opcion:");

        scanf("%c", &choice);
        putchar('\n');
        getchar();

        identify_choice(choice);
    }

}

int identify_choice(char c) {

    switch (c)
    {
    case '1':
        
        return 0;
    case '2':
        
        return 0;
    case '3':
        
        return 0;
    case '4':
        
        return 0;
    case '5':
        
        return 0;

    default:
        printf("\t\tOpcion Invalida, asegurese de no tener espacios :%c \n", c);
        return -1;
        break;
    }

    return 0;
}