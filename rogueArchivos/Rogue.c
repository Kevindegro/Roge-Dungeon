      #include <stdio.h>
      #include <stdlib.h>
      #include <time.h>
      #include <unistd.h>
      #define YELLOW  "\033[1;33m"
      #define RED     "\033[1;31m"
      #define BLUE    "\033[1;34m"
      #define RESET   "\033[0m"
      #define YELLOW  "\033[1;33m"
      #define GREEN   "\033[1;32m"
      #define MAGENTA "\033[1;35m"
      #define CYAN    "\033[1;36m"
      #define WHITE   "\033[1;37m"

//EN DONDE ESTAN TODAS LAS FUNCIONES DEL JUEGO:
/* 
limpiar_consola, bienvenida, rellenarMazmorras.
        Estan en RogueFuncionsUno.c
*/
/*
    imprimirMazmorra, actualizarmazmorra,
    desactivarModoCanonico, restaurarModoCanonico,
    movimientos.
        Estan en RogueFuncionsDos.c
*/
/* 
los void opciones,2,3,4,5 estan en:
RogueFuncionesTres.c
(El opcion1 del swich es un conjunto de funciones)
*/

      int main(int argc, char *argv[]) {
          char jugador = '5';
          char mazmorra1[15][15];
          int opcion;
          char nombre[20];

          printf(YELLOW"┌───────────────────────────────────────┐\n"RESET);
          printf(YELLOW"│           Juego de Mazmorra           │\n"RESET);
          printf(YELLOW"└───────────────────────────────────────┘\n"RESET);
          bienvenida(nombre);
          limpiar_consola();
          mostrarMenu();

          while (1) {
              printf(WHITE"Ingrese una opción: "RESET);
              int l = 0;
              if (scanf("%d", &opcion) != 1) {
                  // Limpiar el buffer de entrada en caso de entrada no válida
                  while ((l = getchar()) != '\n');
                  printf(RED"Opción inválida. Por favor, ingrese una opción válida.\n" RESET);
                  continue;
              }

              getchar(); // Captura el Enter después de ingresar la opción

              switch (opcion) {
                  case 1:
                      limpiar_consola();
                       for (int cargando = 0; cargando <= 100; cargando += 5) {
                printf("┌──────────────────────────────────┐\n");
                printf("│          Cargando:%3d%%           │\n", cargando);
                printf("│                                  │\n");
                printf("└──────────────────────────────────┘\n");
                usleep(200000); // Pausa de 0.2 segundos
                limpiar_consola();
              }
                      rellenarMazmorras(15, mazmorra1, 4);
                      movimientos(15, 15, mazmorra1, jugador);
                      limpiar_consola();
                      mostrarMenu();
                      break;
                  case 2:
                      opcion2();
                      limpiar_consola();
                      mostrarMenu();
                      break;
                  case 3:
                      opcion3();
                      limpiar_consola();
                      mostrarMenu();
                      break;
                  case 4:
                      opcion4();
                      limpiar_consola();
                      mostrarMenu();
                      break;
                  case 5:
                      opcion5();
                      limpiar_consola();
                      mostrarMenu();
                      break;
                  case 6:
                      limpiar_consola();
                       for (int i = 0; i <= 100; i += 10) {
                     for (int i = 0; i < 3; i++) {
          printf(WHITE"┌─────────────────────────┐\n"RESET);
          printf(WHITE"│       Saliendo"RESET);
          for (int j = 0; j <= i; j++) {
              printf(WHITE"."RESET);
          }
          printf(WHITE"       │\n"RESET);
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
