#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include "RogueVoids.h"

#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

#define CRAW "\U0001f980"

void limpiar_consola() {
    printf("\033[H\033[J");
}

void bienvenida(char nombre[20]) {
    while (1) {
        printf(WHITE"Bienvenido jugador. Ingrese su nombre: "RESET);
        scanf("%s", nombre);
        limpiar_consola();
        break;
    }
}

void rellenarMazmorras(int tamañomazmorra, char dungeon[tamañomazmorra][tamañomazmorra], int dificultad) {
    srand(time(NULL));
    int r;
    char enemigos[2] = {'C', 'W'};
    for (int i = 0; i < tamañomazmorra; i++) {
        for (int j = 0; j < tamañomazmorra; j++) {
            r = rand() % 70;
            if (r > dificultad) {
                dungeon[i][j] = '*';
            } else {
                dungeon[i][j] = enemigos[rand() % 2];
            }
        }
    }
}
