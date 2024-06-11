#include <stdio.h>
#include <stdlib.h>

void reproducirMusica(const char *archivo) { //Creamos un char que detecte el archivo
    char comando[256];
    snprintf(comando, sizeof(comando), "ROGUESONGCUBECAVERN.mp3 %s", archivo); //mpg123
    //Este snprintf elige un comando, usa sizeof para leer el array y usa un nombre de un archivo (el cual esta
    //subido al proyecto) y se usa el char de archivo que detecta cosas en otros lugares gracias al "*"
    system(comando); //Ejecuta el comando
}