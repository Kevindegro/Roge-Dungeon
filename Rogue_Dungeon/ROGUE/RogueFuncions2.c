#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include "RogueVoids.h"
#include <locale.h>
//ESTA PARTE DE LAS FUNCIONES INCLUYEN:
//1. imprimirMazmorra, para que en la consola podamos ver todo el mapa del juego.
//2. actualizarmazmorra, para que en la consola se vean los cambios que pasan mientras el usuario juega al juego.
//2. Dos funciones (desactivarModoCanonico, restaurarModoCanonico). Las cuales sirven para que a la hora de moverse con W, A, S, D. No sea necesario el "Enter" para moverse.

//Colores 
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m" 
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

void imprimirMazmorra(int tamañomazmorra, char dungeon[tamañomazmorra][tamañomazmorra], int fila, int columna) {
    printf("--------------\n");
    char esqueleto[] = "☠️"; //Esto es para que se vea el enemigo con calavera
    char asterisco[] = "✳️"; //Para que los asteriscos se vean en la consola de est manera
    char diablo[] = "🤺"; //Esto es para que se vea el enemigo wariorr
    char guardado;
    setlocale(LC_ALL, ""); //Esto añade a los emojis (para usarlos)

    //Estos dos fors viajan por toda la matriz y buscan donde estan sus respectivas cosas
    //(Osea, la calavera, el demonio o los asteriscos) y asi las asigna respectivamente
  for (int i = fila - 3; i <= fila + 3; i++) { 
      for (int j = columna - 3; j <= columna + 3; j++) {
          if (dungeon[i][j] == 'W') {
               printf(MAGENTA"%-4s" RESET, diablo);  // Imprimir emoji
           }
             else if (dungeon[i][j] == 'C') {
                     printf(RED"%s " RESET, esqueleto);  // Imprimir emoji
                 }
             else if (dungeon[i][j] == '*') {
                     printf("%s ", asterisco);  // Imprimir emoji
                 }
                 else if (dungeon[i][j] == '@') {
                         printf(YELLOW"%-4s"RESET, "😎");  // Imprimir emoji del jugador
                     } 
          else if (i >= 0 && i < tamañomazmorra && j >= 0 && j < tamañomazmorra) {
              printf("%c ", dungeon[i][j]);
      } 
      else {
              printf("  ");
          }
      }
      printf("\n");
  }
printf("--------------\n");
}

void actualizar_mazmorra(int n, char mazmorra[n][n], int fila, int columna, int fila_nueva, int columna_nueva, char *original) { //Esta funcion sirve para actualizar la matriz mientras se mueve el jugador
    
  mazmorra[fila][columna] = *original; // Restaurar el valor original
  *original = mazmorra[fila_nueva][columna_nueva]; // Guardar el valor de la nueva casilla
  mazmorra[fila_nueva][columna_nueva] = '@'; // Mover al jugador
}