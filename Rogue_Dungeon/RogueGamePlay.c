#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 
#include <unistd.h>
#include <termios.h>
#include "RogueVoids.h"
#include <locale.h>
//ESTA PARTE DE LAS FUNCIONES INCLUYEN:
// 1. pelea, una funcion aun en proceso para el momento en donde tengamos que luchar contra un enemigo.
// 2. movimientos, el cual sirve para que el usuario mueva a su jugador, esta incluye muchas cosas como funciones de desactivarmodoCanonico (para sacar la necesidad de presionar "enter"), if's (Para lograr moverse), whiles, llamado de funciones como "imprimirMazmorra", etc.
//3. Mostrarmapa, el cual sirve para que el jugador abra el mapa y vea su ubicacion.

#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

//-------------------------------------------------------------------------------------------------------

void mostrarmapa(int tamanomazmorra, char mazmorra[tamanomazmorra][tamanomazmorra], char jugador, struct caracteristicas player){
    //Esta funcion sirve para que el jugador vea su ubicacion en el mapa (Con la tecla M)
    limpiar_consola();
    
    printf("-----------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i <= tamanomazmorra; i++) {
        for (int j = 0; j <= tamanomazmorra; j++) {
            //Esto va a imrprimir "?" en donde esten los enemigos y futuros objetos, pone "?" ya que la idea
            //Es que no sepas que cosa hay encada lugar si es que usas el mapa para orientarte.
            //Tampoco vamos a mostrar donde esta el jugador
            if(mazmorra[i][j] == 'C' || mazmorra[i][j] == 'W' || mazmorra[i][j] == 'B' || mazmorra[i][j] == 'D' || mazmorra[i][j] == 'V'){
                printf("%c ", '?');
            }  
            else if(mazmorra[i][j] == '@'){
                if(player.brujula){ 
                    printf(RED"@ "RESET); 
                }
                else { 
                    printf(". "); 
                }
            } 
            else {
                printf("%c ", mazmorra[i][j]);
            }
        }
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("Presione enter para seguir moviendose\n");
    while (getchar() != '\n');
    limpiar_consola();
}

//-------------------------------------------------------------------------------------------------------

void menu(struct caracteristicas jugador){
    limpiar_consola();
    cargarImagen("ROGUE/Txt/sProtagonist.txt");
    printf("\nVida: %d\n", jugador.vida);
    printf("Ataque(maximo): %d\n", jugador.ataque);
    printf("Resistencia: %d\n", jugador.resistencia);
    printf("Experiencia: %d/%d\n", jugador.experiencia, jugador.experienciaSubirNivel);
    printf("Curaciones: %d💉\n", jugador.curaciones);
    printf("%s\n", jugador.brujula ? "🧭" : " ");
    printf("Presione enter para seguir moviendose\n");
    while (getchar() != '\n');
    limpiar_consola();
}

//-------------------------------------------------------------------------------------------------------

int movimientos(int tamanomazmorra, char mazmorra[tamanomazmorra][tamanomazmorra], char jugador[], struct caracteristicas player) {
    srand(time(NULL));
    //Asigna todos los ints que necesita la fucion movimientos
    int fila = player.fila;
    int columna = player.columna;
    int nuevafila = fila;
    int nuevacolumna = columna;
    char movimiento;
    int moves = 1;
    char original = '.';
    limpiar_consola();
    imprimirMazmorra(tamanomazmorra, mazmorra, fila, columna, player); //Imprime la mazmorra

    struct termios old_tio; //Llama a la funcion para que no se necesite presionar enter
    desactivarModoCanonico(&old_tio);
    while (1) {
        while(moves == 1){
            movimiento = getchar();  // Lee un carácter sin necesidad de presionar Enter
            //(Por el struct de arriba)

            //Los movimientos:
            if (movimiento == 'w' || movimiento == 'W') {
                nuevafila = fila - 1;
                nuevacolumna = columna;
            } else if (movimiento == 'a' || movimiento == 'A') {
                nuevafila = fila;
                nuevacolumna = columna - 1;
            } else if (movimiento == 's' || movimiento == 'S') {
                nuevafila = fila + 1;
                nuevacolumna = columna;
            } else if (movimiento == 'd' || movimiento == 'D') {
                nuevafila = fila;
                nuevacolumna = columna + 1;
            } 
            else if ((movimiento == 'c' || movimiento == 'C') && player.curaciones >= 1) {
                player.vida += 7;
                player.curaciones--;
            }
            else if(movimiento == 'm' || movimiento == 'M'){ //Este es para elegir el mapa
                //LLam a la funcion de mapa
                mostrarmapa(tamanomazmorra, mazmorra, jugador, player);
            }
            else if(movimiento == 'q' || movimiento == 'Q'){ //Este es para elegir el menu
                //LLam a la funcion de menu
                menu(player);
            } 
            else {
                limpiar_consola();
                imprimirMazmorra(tamanomazmorra, mazmorra, fila, columna, player);
                //Si apreta otro boton no asignado, dice que es una opcion invalida
                puts("Opcion invalida");
                continue;
            }
            if (mazmorra[nuevafila][nuevacolumna] == 'V') {
                player.curaciones++;
            }
            if (mazmorra[nuevafila][nuevacolumna] == 'B') {
                player.brujula = true;
            }
            if (mazmorra[nuevafila][nuevacolumna] == ' ') {
                limpiar_consola();
                imprimirMazmorra(tamanomazmorra, mazmorra, fila, columna, player);
                puts("Movimiento fuera de los límites.");
                continue;
                //Si estas en el borde de la matriz y te moves hacia un lugar que no vale nada
                //Se activa este if
            }
            //Actualiza la mazmorra (esto es para cuando nos movamos)
            actualizar_mazmorra(tamanomazmorra, mazmorra, fila, columna, nuevafila, nuevacolumna, &original, player);
            fila = nuevafila;
            columna = nuevacolumna;
            player.fila = fila;
            player.columna = columna;
            limpiar_consola();
            imprimirMazmorra(tamanomazmorra, mazmorra, fila, columna, player); //Esta parte de todos los if junto a esta variable
            //Hacen que si estas parado a la derecha, izquierda, arriba o abajo (por eso mismo
            //los +1 de fila y columna) que o detecte e inicie el modo de pelea
            if (mazmorra[fila][columna + 1] == 'C' || mazmorra[fila][columna + 1] == 'W' || mazmorra[fila][columna + 1] == 'D') {
                player.guardado = mazmorra[fila][columna + 1];
            }
            if (mazmorra[fila][columna - 1] == 'C' || mazmorra[fila][columna - 1] == 'W' || mazmorra[fila][columna - 1] == 'D') {
                    player.guardado = mazmorra[fila][columna - 1];
            }
            if (mazmorra[fila + 1][columna] == 'C' || mazmorra[fila + 1][columna] == 'W'|| mazmorra[fila + 1][columna] == 'D') {
                    player.guardado = mazmorra[fila + 1][columna];
            }
            if (mazmorra[fila - 1][columna] == 'C' || mazmorra[fila - 1][columna] == 'W' || mazmorra[fila - 1][columna] == 'D') {
                    player.guardado = mazmorra[fila - 1][columna];
            }
                        
            if ((mazmorra[fila][columna + 1] == 'C' || mazmorra[fila][columna + 1] == 'W' || mazmorra[fila][columna + 1] == 'D') || (mazmorra[fila + 1][columna] == 'C' || mazmorra[fila + 1][columna] == 'W' || mazmorra[fila + 1][columna] == 'D') || (mazmorra[fila][columna - 1] == 'C' || mazmorra[fila][columna - 1] == 'W'|| mazmorra[fila][columna - 1] == 'D') || (mazmorra[fila - 1][columna] == 'C' || mazmorra[fila - 1][columna] == 'W' || mazmorra[fila - 1][columna] == 'D' )) {
                    
                moves = 0;
                printf(RED"Aparecio un enemigo\n"RESET);
                for(int i = 0; i < 5; i++){
                      
                    usleep(200000); //Con esto hace tardar un pequeno tiemp para que se vea
                    //Mas estetico
                }
                limpiar_consola();
                for (int cargando = 0; cargando <= 100; cargando += 10) { //Decoracion
                    printf("┌──────────────────────────────────┐\n");
                    printf("│          Cargando:%3d%%           │\n", cargando);
                    printf("│                                  │\n");
                    printf("└──────────────────────────────────┘\n");
                    usleep(200000); // Pausa de 0.2 segundos
                    limpiar_consola();
                }
                pelea(player, tamanomazmorra, mazmorra, jugador);
            }
        }
    }
    restaurarModoCanonico(&old_tio); //Pone la termios como antes
    player.enemigoDerrotado = false;
    return 0;
}

//-------------------------------------------------------------------------------------------------------
