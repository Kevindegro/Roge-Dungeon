#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include "RogueVoids.h"
#include <locale.h>
#include <sys/wait.h>

#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

//-------------------------------------------------------------------------------------------------------
void pelea(struct caracteristicas jugador, int tamanomazmorra, char mazmorra[tamanomazmorra][tamanomazmorra], char player[]) {
    struct enemigo {
        int vida;
        int ataque;
        int resistencia;
    };

    struct enemigo esqueleto; //Asignamos vida, ataque y resistencia a esqueleto
    esqueleto.vida = 3;
    esqueleto.ataque = 2;
    esqueleto.resistencia = 3;

    struct enemigo diablo; //Asignamos vida, ataque y resistencia a guerrero
    diablo.vida = 6;
    diablo.ataque = 3;
    diablo.resistencia = 4;

    struct enemigo devil; //Asignamos vida, ataque y resistencia a guerrero
    devil.vida = 10;
    devil.ataque = 7;
    devil.resistencia = 20;

    struct enemigo* enemigoPelea; //Con esta variable podemos cambiar el enemigo que se enfrenta
    if (jugador.guardado == 'C') { //Aca es donde usamos punteros (* en enemigo de la linea 39)
        enemigoPelea = &esqueleto; //y aca el "&"
    } else if (jugador.guardado == 'W') {
        enemigoPelea = &diablo; //y aca el "&"
    } else if (jugador.guardado == 'D') {
        enemigoPelea = &devil; //y aca el "&"
    } else {
        return;
    }

    int eleccion;
    bool escapar = false; // Variable para manejar la escapada
    while (!escapar) {
        if (enemigoPelea->resistencia <= 0) {
             enemigoPelea->vida += enemigoPelea->resistencia;
             enemigoPelea->resistencia = 0; 
        }
        limpiar_consola();
        if (jugador.guardado == 'C') {
            cargarImagen("ROGUE/Txt/skull.txt");
            printf("\n 😎                       ⚔️                        ☠️\n");
        }
        if (jugador.guardado == 'W') {
            cargarImagen("ROGUE/Txt/warrior.txt");
            printf("\n 😎                       ⚔️                        🛡️\n");
        }
        if (jugador.guardado == 'D') {
            cargarImagen("ROGUE/Txt/devil.txt");
            printf("\n 😎                       ⚔️                        😈\n");
        }
        printf(" ┌───────────────────┐          ┌────────────────────┐\n");
        printf(" │ Vida: %2d          │          │ Vida: %2d           │\n", jugador.vida, enemigoPelea->vida);
        printf(" │ Resistencia: %2d   │          │ Resistencia: %2d    │\n", jugador.resistencia, enemigoPelea->resistencia);
        printf(" └───────────────────┘          └────────────────────┘\n");
        printf("Elija su movimiento:\n");
        printf(RED"Ataque básico (1)\n"RESET);
        printf(CYAN"Defenderse (2)\n"RESET);
        printf(RED"Curarse (3)\n"RESET);
        scanf("%d", &eleccion);
    
        if (eleccion > 4 || eleccion < 1) { 
            printf(RED"Opción inválida. Por favor, ingrese una opción válida.\n" RESET);
            continue;
        }

        if (eleccion == 1) { // Ataque básico
            if (enemigoPelea->resistencia <= 0) {
                enemigoPelea->vida += enemigoPelea->resistencia;
            }
            if (enemigoPelea->resistencia == 0) {
                enemigoPelea->vida -= jugador.ataque;
            } else {
                enemigoPelea->resistencia -= jugador.ataque;
            }
        } else if (eleccion == 2) { // Defenderse
            jugador.resistencia += 3;
        } else if (eleccion == 3 && jugador.curaciones > 0) { // Curarse
            jugador.vida += 7;
            jugador.curaciones--;
        }

        if (enemigoPelea->vida <= 0) { 
            if(jugador.guardado == 'D') {
                limpiar_consola();
                cargarImagen("ROGUE/Txt/VICOTIRA.txt");
                printf(CYAN"\n\nAhora eres el rogue %s"RESET,jugador.nombre);
                exit(0);
            }
            escapar = true;
            jugador.enemigoDerrotado = true;
            while (getchar() != '\n');
            limpiar_consola();
            jugador.experiencia += 5;
            if(jugador.experiencia >= jugador.experienciaSubirNivel){
                jugador.ataque += 2;
                jugador.experiencia = 0;
            }
            movimientos(tamanomazmorra, mazmorra, player, jugador);
            printf(RED"\nDerrotaste al enemigo\n"RESET);
            // No es necesario reiniciar `escapar` y `jugador.enemigoDerrotado` aquí
            jugador.guardado = ' ';
            return; // Salir de la función después de derrotar al enemigo
        }

        // Animacion de la pelea
        limpiar_consola();
        cargarImagen("ROGUE/Txt/combate.txt");
        printf(RED"\nEsperando el movimiento del enemigo. . . . .\n"RESET);
        usleep(1000000);
        limpiar_consola();
        cargarImagen("ROGUE/Txt/combateDos.txt");
        printf(RED"\nEsperando el movimiento del enemigo. . . . .\n"RESET);
        usleep(1000000);
        limpiar_consola();
        cargarImagen("ROGUE/Txt/combate.txt");
        printf(RED"\nEsperando el movimiento del enemigo. . . . .\n"RESET);
        usleep(1000000);
        limpiar_consola();
        cargarImagen("ROGUE/Txt/combateDos.txt");
        printf(RED"\nEsperando el movimiento del enemigo. . . . .\n"RESET);
        usleep(1000000);
        limpiar_consola();

        // Movimiento del enemigo
        if (jugador.resistencia >= 1) {
            jugador.resistencia -= enemigoPelea->ataque;
        } 
        if (jugador.resistencia <= 0) {
            jugador.resistencia = 0;
            if(eleccion == 3){
                 jugador.resistencia += 3;
                 jugador.resistencia -= enemigoPelea->ataque;
            }
        }
        if (jugador.resistencia <= 0) {
            jugador.vida -= enemigoPelea->ataque;
        }
        if (jugador.resistencia < 0) { 
            jugador.vida += jugador.resistencia; // Restar la resistencia negativa a la vida
            jugador.resistencia = 0;
        }
        if(jugador.vida == 0 || jugador.vida <= 0) {
            limpiar_consola();
            cargarImagen("ROGUE/Txt/PERDISTE.txt");
            exit(0);
        }
    }
    // Verifica si el jugador escapó y maneja eso fuera del bucle
} //-------------------------------------------------------------------------------------------------------
