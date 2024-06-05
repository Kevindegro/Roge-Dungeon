#ifndef ROGUEVOIDS_H
#define ROGUEVOIDS_H

void limpiar_consola();
void bienvenida(char nombre[20]);
void rellenarMazmorras(int tamañomazmorra, char dungeon[tamañomazmorra][tamañomazmorra], int dificultad);
void imprimirMazmorra(int tamañomazmorra, char dungeon[tamañomazmorra][tamañomazmorra], int fila, int columna);
void actualizar_mazmorra(int n, char mazmorra[n][n], int fila, int columna, int fila_nueva, int columna_nueva, char *original);
void desactivarModoCanonico(struct termios *old_tio);
void restaurarModoCanonico(struct termios *old_tio);
int movimientos(int Nmazmorra, int tamañomazmorra, char mazmorra[tamañomazmorra][tamañomazmorra], char jugador);
void opcion2();
void opcion3();
void opcion4();
void opcion5();
void mostrarMenu();

#endif // ROGUEVOIDS_H
