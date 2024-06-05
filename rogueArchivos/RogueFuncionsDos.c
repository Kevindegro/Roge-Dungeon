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
        #define SKULL "\U0001f480"

        void imprimirMazmorra(int tamañomazmorra, char dungeon[tamañomazmorra][tamañomazmorra], int fila, int columna) {
            for (int i = fila - 1; i <= fila + 1; i++) {
                for (int j = columna - 1; j <= columna + 1; j++) {
                    if (i >= 0 && i < tamañomazmorra && j >= 0 && j < tamañomazmorra) {
                       /* if(dungeon[i][j] == 'C') {
                            dungeon[i][j] = printf(SKULL " ");
                            } */
                        printf("%c ", dungeon[i][j]);
                } else {
                        printf("  ");
                    }
                }
                printf("\n");
            }
        }

        void actualizar_mazmorra(int n, char mazmorra[n][n], int fila, int columna, int fila_nueva, int columna_nueva, char *original) {
            mazmorra[fila][columna] = *original; // Restaurar el valor original
            *original = mazmorra[fila_nueva][columna_nueva]; // Guardar el valor de la nueva casilla
            mazmorra[fila_nueva][columna_nueva] = '@'; // Mover al jugador
        }

        void desactivarModoCanonico(struct termios *old_tio) {
            struct termios new_tio;

            // Guardar la configuración actual del terminal
            tcgetattr(STDIN_FILENO, old_tio);

            // Desactivar el modo canónico y el eco
            new_tio = *old_tio;
            new_tio.c_lflag &= (~ICANON & ~ECHO);
            new_tio.c_cc[VMIN] = 1;
            new_tio.c_cc[VTIME] = 0;

            // Establecer los nuevos atributos
            tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
        }

        void restaurarModoCanonico(struct termios *old_tio) {
            // Restaurar los atributos del terminal
            tcsetattr(STDIN_FILENO, TCSANOW, old_tio);
        }

        int movimientos(int Nmazmorra, int tamañomazmorra, char mazmorra[tamañomazmorra][tamañomazmorra], char jugador) {
            srand(time(NULL));
            int fila = rand() % Nmazmorra;
            int columna = rand() % Nmazmorra;
            int nuevafila = fila;
            int nuevacolumna = columna;
            char movimiento;
            char original = mazmorra[fila][columna];
            mazmorra[fila][columna] = jugador;
            limpiar_consola();
            imprimirMazmorra(tamañomazmorra, mazmorra, fila, columna);

            struct termios old_tio;
            desactivarModoCanonico(&old_tio);

            while (1) {
                movimiento = getchar();  // Lee un carácter sin necesidad de presionar Enter

                if (movimiento == 'w') {
                    nuevafila = fila - 1;
                    nuevacolumna = columna;
                } else if (movimiento == 'a') {
                    nuevafila = fila;
                    nuevacolumna = columna - 1;
                } else if (movimiento == 's') {
                    nuevafila = fila + 1;
                    nuevacolumna = columna;
                } else if (movimiento == 'd') {
                    nuevafila = fila;
                    nuevacolumna = columna + 1;
                } else {
                    limpiar_consola();
                    imprimirMazmorra(tamañomazmorra, mazmorra, fila, columna);
                    puts("Opción inválida");
                    continue;
                }

                if (nuevafila < 0 || nuevafila >= Nmazmorra || nuevacolumna < 0 || nuevacolumna >= Nmazmorra) {
                    limpiar_consola();
                    imprimirMazmorra(tamañomazmorra, mazmorra, fila, columna);
                    puts("Movimiento fuera de los límites.");
                    continue;
                }

                actualizar_mazmorra(tamañomazmorra, mazmorra, fila, columna, nuevafila, nuevacolumna, &original);
                fila = nuevafila;
                columna = nuevacolumna;
                limpiar_consola();
                imprimirMazmorra(tamañomazmorra, mazmorra, fila, columna);
            }

            restaurarModoCanonico(&old_tio);
            return 0;
        }
