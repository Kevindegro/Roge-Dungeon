#ifndef ROGUEVOIDS_H
#define ROGUEVOIDS_H

//En todo este archivo se encuentran las funciones que se usan en el main
//Es necesario declararlas para que se detecten en todos los demas archivos
//Esta es la caracteristica carpeta que tenemos llamada: #include "RogueVoids.h"

struct caracteristicas {
    int vida;
    int resistencia;
    int ataque;
    int experiencia;
};
void limpiar_consola(); 
void bienvenida(char nombre[20]);
void rellenarMazmorras(int tamañomazmorra, char dungeon[tamañomazmorra][tamañomazmorra]);
void imprimirMazmorra(int tamañomazmorra, char dungeon[tamañomazmorra][tamañomazmorra], int fila, int columna);
void actualizar_mazmorra(int n, char mazmorra[n][n], int fila, int columna, int fila_nueva, int columna_nueva, char *original);
void desactivarModoCanonico(struct termios *old_tio);
void restaurarModoCanonico(struct termios *old_tio);
int movimientos(int Nmazmorra, int tamañomazmorra, char mazmorra[tamañomazmorra][tamañomazmorra], char jugador[], struct caracteristicas player);
void opcion2();
void opcion3();
void opcion4();
void opcion5();
void enemigo1();
void enemigo2();
void mostrarMenu();
void pelea(char enemigo, struct caracteristicas jugador);
void mostrarmapa(int tamañomazmorra, char mazmorra[tamañomazmorra][tamañomazmorra], char jugador);
void cargarImagen(char *nonvre);
void reproducirMusica(const char *archivo);
#endif // ROGUEVOIDS_H