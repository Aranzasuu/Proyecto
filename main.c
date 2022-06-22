#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Map.h"
#include "list.h"
#include "funciones.h"

int main(){
    Red *total = crearRed();

    FILE *archivo = fopen("100usuarios.csv","r");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
        return(EXIT_FAILURE);
    }
    importar(archivo,total);

    ingresarApp(total);
    return 0;
}