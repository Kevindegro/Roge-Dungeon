      #include <stdio.h>
      #include <stdlib.h>
      #include <time.h>
      #include <unistd.h> //Esta libreria sirve para añadir los colores
      #include <locale.h>
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
      #define SKULL "\U0001f480"
    //Este es el main, tiene un swich el cual tiene las llamadas a funciones.
      int main(int argc, char *argv[]) {
          setlocale(LC_ALL, ""); //Añade la "funcion" (por asi decirlo) para colocar emojis
          char simbolo[]= "😎"; //Creamos una variable para el emoji (Este es el protagonista)
          struct caracteristicas { //Esta estructura sirve para añadir caracteristicas
          //Este struct almacena varios ints, parecido a un array (No tienen nada que ver, 
          //es un ejemplo de comparacion)
                int vida;
                int resistencia;
                int ataque;
                int experiencia;
            };
          struct caracteristicas jugador; //Este struct almacena las caracteristicas del jugador (se las asigna)
          jugador.vida = 12;
           jugador.resistencia = 20;
           jugador.ataque= 20;
           jugador.experiencia = 10;
          
          //declara la mazmorra y su tamaño
          char mazmorra[50][50];
          int opcion;
          //nombre del jugador
          char nombre[20];

          printf(YELLOW"                    ┌───────────────────────────────────────┐\n"RESET);
          printf(YELLOW"                    │           R   O   G   U   E           │\n"RESET);
          printf(YELLOW"                    └───────────────────────────────────────┘\n"RESET);
          bienvenida(nombre);
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
                usleep(200000); // Pausa de 0.2 segundos
                limpiar_consola();
              }
                      rellenarMazmorras(50, mazmorra);
                      movimientos(50, 50, mazmorra, simbolo, jugador);
                      limpiar_consola();
                      mostrarMenu();
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