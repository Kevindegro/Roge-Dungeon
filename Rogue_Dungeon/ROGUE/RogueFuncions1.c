#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include "RogueVoids.h"

//ESTA PARTE DE LAS FUNCIONES INCLUYEN:
//1. Limpiar consola: Para limpiar la consola como si fuese un system("clear");
//2. Bienvenida: Para imprimir el menu donde ubicamos nuestro nombre para el jugador.
//3. Rellenar mazmorras: Para rellenar las mazmorras con los enemigos y los * respectivos.

//Colores
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m" 
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

//Este era un intento de emoji, ya encontramos otra manera de tenerlos pero por ahora vamos a dejarla, a lo mejor nos sirev en el futuro
#define CRAW "\U0001f980"

void limpiar_consola() {
    printf("\033[H\033[J"); //Esto limpia la consola, como un system("clear") pero mas efectivo
}
// \033[H lleva el cursor de la consola a la posición superior izquierda y \033[J borra desde la posición actual del cursor hasta el final de la pantalla.

void bienvenida(char nombre[20]) { //Esta funcion es la primera que aparece en el juego, pide un nombre de no mas de 20 caracteres
    while (1) {
        printf(WHITE"                    Bienvenido jugador. Ingrese su nombre: "RESET); //Asi se pone colores 
        //Con "WHITE" o cualquier color definido, y siempre al final "RESET" (Para que se vuelva a su color original)
        scanf("%s", nombre);
        limpiar_consola();
        break;
    }
}

void rellenarMazmorras(int tamañomazmorra, char dungeon[tamañomazmorra][tamañomazmorra]) {
    srand(time(NULL));
    int r;
    int rango = 10;
    char enemigos[2] = {'C', 'W'}; // Declara a los enemigos C y W para imprimirlos en la matriz
    for (int i = 0; i < tamañomazmorra; i++) { // Un for que indica el tamaño de la mazmorra
        for (int j = 0; j < tamañomazmorra; j++) {
            r = rand() % 70; // Este rand limita el numero de enemigos que se pueden encontrar en la mazmorra
            // Mientras mas grande, menor la cantidad
            if (r > rango) {
                dungeon[i][j] = '*'; // pone * en los lugares de la matriz vacios
            } 
            else {
                dungeon[i][j] = enemigos[rand() % 2]; // Pone los enemigos si es que r es menor a rango
            }
        }
    }
}