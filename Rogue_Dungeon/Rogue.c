#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h> // Permite la modificacion del termios
#include <locale.h>
#include <stdbool.h>
#include <string.h>
//Todos estos son los colores que agregamos
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"
#define YELLOW  "\033[1;33m"
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
      
//Este es el main, tiene un swich el cual tiene las llamadas a funciones.
int main(int argc, char *argv[]) {
    setlocale(LC_ALL, ""); //Anade la "funcion" (por asi decirlo) para colocar emojis
    char simbolo[]= "😎"; //Creamos una variable para el emoji (Este es el protagonista)
    int habitaciones[10][4];
    int fila, columna;
    int tamanomazmorra = 40;
    char dungeon[tamanomazmorra][tamanomazmorra];
    struct caracteristicas { //Este es un struct de las caracteristicas del jugador
        int vida; 
        int resistencia;
        int ataque;
        int experiencia;
        int curaciones;
        bool brujula;
        int experienciaSubirNivel;
        int fila;
        int columna;
        bool enemigoDerrotado;
        char guardado;
        char nombre[20];
    };
    struct caracteristicas jugador; //Este struct almacena las caracteristicas del jugador (se las asigna)
    jugador.fila = 0;
    jugador.columna = 0;
    jugador.vida = 12;
    jugador.resistencia = 2;
    jugador.ataque= 4;
    jugador.experiencia = 10;
    jugador.curaciones = 0;
    jugador.brujula = false;
    jugador.experienciaSubirNivel = 20;
    jugador.enemigoDerrotado = false;
    jugador.guardado = ' ';
    jugador.nombre[20] = " ";
    //declara la mazmorra y su tamano
    int opcion;

    printf(YELLOW"                    ┌───────────────────────────────────────┐\n"RESET);
    printf(YELLOW"                    │           R   O   G   U   E           │\n"RESET);
    printf(YELLOW"                    └───────────────────────────────────────┘\n"RESET);
    bienvenida(jugador);
    limpiar_consola();
    mostrarMenu();
    //Opciones para que el jugador elija
    while (1) {
        setlocale(LC_ALL, ""); 
        printf(WHITE"Ingrese una opción: "RESET);
        int l = 0;
        if (scanf("%d", &opcion) != 1) {
            // Limpiar el buffer de entrada en caso de entrada no válida
            while ((l = getchar()) != '\n');
            limpiar_consola();
            mostrarMenu();
            printf(RED"Opción inválida. Por favor, ingrese una opción válida.\n" RESET);
            continue;
        }

        getchar(); // Captura el Enter después de ingresar la opción

        switch (opcion) {
            case 1: //Empieza el juego y comienza una pantalla de carga "Animada"
                limpiar_consola();
                for (int cargando = 0; cargando <= 100; cargando += 5) {
                    printf("┌──────────────────────────────────┐\n");
                    printf("│          Cargando:%3d%%           │\n", cargando);
                    printf("│                                  │\n");
                    printf("└──────────────────────────────────┘\n");        
                    usleep(200000);     // Pausa de 0.2 segundos
                    limpiar_consola();
                }
                inicializarMazmorra(tamanomazmorra, dungeon);
                generarHabitaciones(tamanomazmorra, dungeon, habitaciones);
                conectarHabitaciones(tamanomazmorra, dungeon, habitaciones);
                colocarEnemigos(tamanomazmorra, dungeon);
                for (int i = 0; i < 1; i++) {
                     jugador.fila = rand() % tamanomazmorra;
                     jugador.columna = rand() % tamanomazmorra;
                    if (dungeon[jugador.fila][jugador.columna] == '.') {
                        dungeon[jugador.fila][jugador.columna] = '@'; 
                    }
                    else{
                        i--;
                    }
                }
                movimientos(tamanomazmorra, dungeon, simbolo, jugador, fila, columna);
                break;
            case 2: //Muestra las reglas del juego
                opcion2();
                limpiar_consola();
                mostrarMenu();
                break;
            case 3: //Muestra los controles del juego
                opcion3();
                limpiar_consola();
                mostrarMenu();
                break;
            case 4: //Muestra los enemigos del juego
                opcion4();
                limpiar_consola();
                mostrarMenu();
                break;
            case 5: //Muestra los Objetos que aparecen en el juego
                opcion5();
                limpiar_consola();
                mostrarMenu();
                break;
            case 6: //Cierra el juego
                limpiar_consola();
                for (int i = 0; i <= 100; i += 10) {
                    for (int i = 0; i < 3; i++) {
                        printf(WHITE"┌─────────────────────────┐\n"RESET);
                        printf(WHITE"        Saliendo"RESET);
                        for (int j = 0; j <= i; j++) {
                            printf(WHITE"."RESET);
                        }
                        printf(WHITE"        \n"RESET);
                        printf(WHITE"└─────────────────────────┘\n"RESET);
                        usleep(200000); // 200,000 microsegundos = 0.2 segundos
                        limpiar_consola();
                    }
                    usleep(200000);
                    limpiar_consola();
                }
                return 0;
            default:
                limpiar_consola();
                printf(RED"Opción inválida. Por favor, ingrese una opción válida.\n"RESET);
                mostrarMenu();
                break;
        }
    }
    return 0;
}
