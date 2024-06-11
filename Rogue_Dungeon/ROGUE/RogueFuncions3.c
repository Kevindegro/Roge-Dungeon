            #include <stdio.h>
            #include <stdlib.h>
            #include <time.h>
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

            void pelea(char enemigo, struct caracteristicas jugador) { //Hace un struct del jugador para que
                //Empiece a detectar lo de la lucha
                setlocale(LC_ALL, ""); //Inicia para usar emojis (se puede pensar como lo que usamos de 
                // srand(time(NULL));)
                limpiar_consola();
                struct enemigo { //Asigna al enemigo sus valores de estadisticas
                int vida;
                int ataque;
                int resistencia;
                };
                
                struct enemigo esqueleto; //Asigna al esqueleto sus valores de estadisticas
                esqueleto.vida = 5;
                esqueleto.ataque = 5;
                esqueleto.resistencia = 2;
                
                struct enemigo diablo; //Asigna al esqueleto sus valores de estadisticas
                diablo.vida = 10;
                diablo.ataque = 10;
                diablo.resistencia = 5;

                //En estos dos ifs, se agarra la funcion "cargarImagen" y dentro de ella, mediante fopen
                //Se abre  
                if(enemigo == 'C') {cargarImagen("skull.txt"); //Carga la imagen del enemigo de la calavera
                printf("\n 😎                      ⚔️                        ☠️\n");
                                   }
                if(enemigo == 'W') {cargarImagen("warrior.txt");//Carga la imagen del enemigo del demonio
                printf("\n 😎                      ⚔️                        🛡️\n");
                                   }//Decoracion al momento de la pelea
              printf(" ┌──────────────────┐          ┌───────────────────┐\n");
              printf(" │ Vida: %d         │          │ Vida: %d           │\n", jugador.vida, esqueleto.vida);
              printf(" │ Resistencia: %d  │          │ Resistencia: %d    │\n", jugador.resistencia, esqueleto.resistencia);
              printf(" └──────────────────┘          └───────────────────┘\n");
                printf("Elija su movimiento:\n");
                printf(CYAN"Ataque basico (1)\n"RESET);
                printf(RED"Ataque pesado (2)\n"RESET);
                printf(CYAN"Defenderse (3)\n"RESET);
                printf(RED"Escapa! (4)\n"RESET);
            }
void mostrarmapa(int tamañomazmorra, char mazmorra[tamañomazmorra][tamañomazmorra], char jugador){
    //Esta funcion sirve para que el jugador vea su ubicacion en el mapa (Con la letra M)
    limpiar_consola();
     printf("-----------------------------------------------------------------------------------------------------\n");
      for (int i = 0; i <= tamañomazmorra; i++) {
          for (int j = 0; j <= tamañomazmorra; j++) {
              //Esto va a imrprimir "?" en donde esten los enemigos y futuros objetos, pone "?" ya que la idea
              //Es que no sepas que cosa hay encada lugar si es que usas el mapa para orientarte.
              //Tampoco vamos a mostrar donde esta el jugador
           if(mazmorra[i][j] == 'C' || mazmorra[i][j] == 'W'){
              printf("%c ", '?');
          } 
                
             else if(mazmorra[i][j] == '@'){
                     printf("%c", '*'); //Si es que detecta un @ en el lugar, imprime un ""
                 } 
          else{
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
            int movimientos(int Nmazmorra, int tamañomazmorra, char mazmorra[tamañomazmorra][tamañomazmorra], char jugador[], struct caracteristicas player) {
                srand(time(NULL));
                //Asigna todos los ints que necesita la fucion movimientos
                int fila = rand() % Nmazmorra; 
                int columna = rand() % Nmazmorra;
                int nuevafila = fila;
                int nuevacolumna = columna;
                char movimiento;
                char original = mazmorra[fila][columna];
                mazmorra[fila][columna] = '@'; 
                limpiar_consola();
                imprimirMazmorra(tamañomazmorra, mazmorra, fila, columna); //Imprime la mazmorra

                struct termios old_tio; //Llama a la funcion para que no se necesite presionar enter
                desactivarModoCanonico(&old_tio);

                while (1) {
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
                    } else if(movimiento == 'm' || movimiento == 'M'){ //Este es para elegir el mapa
                        //LLam a la funcion de mapa
                        mostrarmapa(tamañomazmorra, mazmorra, jugador);
                            }
                    else {
                        limpiar_consola();
                        imprimirMazmorra(tamañomazmorra, mazmorra, fila, columna);
                            //Si apreta otro boton no asignado, dice que es una opcion invalida
                        puts("Opción inválida");
                        continue;
                    }

                    if (nuevafila < 0 || nuevafila >= Nmazmorra || nuevacolumna < 0 || nuevacolumna >= Nmazmorra) {
                        limpiar_consola();
                        imprimirMazmorra(tamañomazmorra, mazmorra, fila, columna);
                        puts("Movimiento fuera de los límites.");
                        continue;
                            //Si estas en el borde de la matriz y te moves hacia un lugar que no vale nada
                            //Se activa este if
                    }
                        //Actualiza la mazmorra (esto es para cuando nos movamos)
                    actualizar_mazmorra(tamañomazmorra, mazmorra, fila, columna, nuevafila, nuevacolumna, &original);
                    fila = nuevafila;
                    columna = nuevacolumna;
                    limpiar_consola();
                    imprimirMazmorra(tamañomazmorra, mazmorra, fila, columna);

                    char guardado; //Esta parte de todos los ifs junto a esta variable
                        //Hacen que si estas parado a la derecha, izquierda, arriba o abajo (por eso mismo
                        //los +1 de fila y columna) que o detecte e inicieel modo de pelea
                    if (mazmorra[fila][columna + 1] == 'C' || mazmorra[fila][columna + 1] == 'W') {
                        guardado = mazmorra[fila][columna + 1];
                    }
                    if (mazmorra[fila][columna - 1] == 'C' || mazmorra[fila][columna - 1] == 'W') {
                        guardado = mazmorra[fila][columna - 1];
                    }
                    if (mazmorra[fila + 1][columna] == 'C' || mazmorra[fila + 1][columna] == 'W') {
                        guardado = mazmorra[fila + 1][columna];
                    }
                    if (mazmorra[fila - 1][columna] == 'C' || mazmorra[fila - 1][columna] == 'W') {
                        guardado = mazmorra[fila - 1][columna];
                    }
                    if ((mazmorra[fila][columna + 1] == 'C' || mazmorra[fila][columna + 1] == 'W') || 
                        (mazmorra[fila + 1][columna] == 'C' || mazmorra[fila + 1][columna] == 'W') || 
                        (mazmorra[fila][columna - 1] == 'C' || mazmorra[fila][columna - 1] == 'W') || 
                        (mazmorra[fila - 1][columna] == 'C' || mazmorra[fila - 1][columna] == 'W')) {
                         printf(RED"Aparecio un enemigo\n"RESET);
                        for(int i = 0; i < 5; i++){
                            usleep(200000); //Con esto hace tardar un pequeño tiemp para que se vea
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
                        pelea(guardado, player);
                    }
                }
                restaurarModoCanonico(&old_tio); //Pone la termios como antes
                return 0;
            }
