#include <stdio.h>
#include <stdlib.h>

#define INTRO "menu.txt"


int print_intro() {

    FILE *file = fopen(INTRO, 'r');

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

        printf("/n/n");
        printf("/t/t 1 - Ordenador por Titulo de la publicacion");
        printf("/t/t 2 - Ordenador por tamano en palabras");
        printf("/t/t 3 - Ordenador por nombre del archivo");
        printf("/t/t 4 - Ordenador por cantidad de palindromos en el abstract");
        printf("/t/t 5 - Salir");
        
        scanf("%c", &choice);

        identify_choice(choice);
    }

}

int identify_choice(char c) {

    switch (c)
    {
    case '1':
        break;
    case '2':
        break;
    case '3':
        break;
    case '4':
        break;
    default:
        printf("\t\tOpcion Invalidad, asegurese de no tener espacios :%c", c);
        break;
    }
}