#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "list.h"
#include "funciones.h"

const char *get_csv_field (char * tmp, int k){
    int open_mark = 0;
    char *ret = (char *) malloc (150 * sizeof(char));
    int ini_i = 0, i = 0, j = 0;
    while(tmp[i+1] != '\0'){

        if(tmp[i] == '\"'){
            open_mark = 1 - open_mark;
            if(open_mark) ini_i = i + 1;
            i++;
            continue;
        }

        if(open_mark || tmp[i] != ','){
            if(k == j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i] == ','){
            if(k == j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i + 1;
        }
        i++;
    }

    if(k == j){

        i = i - 1;
        for (i; tmp[i] != '\0'; i++)
        {
            ret[i - ini_i] =  tmp[i];
        }
       ret[i - ini_i] = 0;
       return ret;
    }
    return NULL;
}

int is_equal_string(void * key1, void * key2) 
{
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

void ingresarApp(Red *total){
    int opcion;
    char nomUsuario[100], contUsuario[100];

    mostrarMapa(total);

    printf("\n\n                 Bienvenidx a TYNDER!\n-------------------------------------------------------\n\n");
    printf(" 1 -> Registrarse\n");
    printf(" 2 -> Iniciar sesion\n");
    printf(" 3 -> Salir\n\n");
    printf("Ingrese su opcion: ");
    
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 3){
        printf("Ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    
    //if(opcion == 1) registrarUsuario(total);

    menu(total);
}

void mostrarMapa(Red *total){
    usuario *usu = firstMap(total->totalUsuarios);
    int cont = 1;

    while(usu != NULL){
        printf("usuario numero #%d\n",cont);
        printf("nombre = %s\n", usu->nombre);
        printf("apodo = %s\n", usu->apodo);
        printf("genero musical fav = %s\n", usu->gustos->generofav);
        cont++;
        usu = nextMap(total->totalUsuarios);
    }
}

/*
void ingresarApp(Red *total){
    int opcion, opcion2;
    char nombreUsu[100], contrasenaUsu[100];

    printf("\n\n                 Bienvenidx a TYNDER!\n-------------------------------------------------------\n\n");
    printf(" 1 -> Registrarse\n");
    printf(" 2 -> Iniciar sesion\n");
    printf(" 3 -> Salir\n\n");
    printf("Ingrese su opcion: ");

    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 3){
        printf("Ingrese una opcion valida\n");
        scanf("%d", &opcion);
    }

    if(opcion == 1) registrarUsuario(total);
    if(opcion == 2){
        printf("Ingrese el nombre de usuario: ");
        scanf("%[^\n]s", nombreUsu);
        printf("\nIngrese la contraseña: ");
        scanf("%[^\n]s", contrasenaUsu);
        if(validarUsuario(total, nombreUsu, contrasenaUsu)) menu(total);
        else 
        {
            printf("Usuario invalido\n");
            printf("Desea volver a ingresar?\n");
            printf("1. SI         2.Registrarse\n");
            scanf("%d",&opcion2);
            if(opcion2 == 1){
                printf("Ingrese el nombre de usuario: ");
                scanf("%[^\n]s", nombreUsu);
                printf("\nIngrese la contraseña: ");
                scanf("%[^\n]s", contrasenaUsu);
                if(validarUsuario(total,nombreUsu,contrasenaUsu)) menu(total);
                else registrarUsuario(total);
            }
        }
    }
    if(opcion == 3){
        printf("\n\n********************************************\nHas salido exitosamente de la aplicacion!\n\n\n");
        return;
    }
}*/

void registrarUsuario(Red *total){
    printf("en proceso");
}

bool validarUsuario(Red *total, char *nombreU, char *contrasenaU){
    usuario *aux = firstMap(total->totalUsuarios);
    while(aux != NULL){
        if(strcmp(nombreU,aux->nombre)) return true;
        aux = nextMap(total->totalUsuarios);
    }
    return false;
}

void impresionMenu(){
    printf("*********** MENU **********\n");
    printf("1. Ingresar Perfil\n");
    printf("2. Editar Perfil\n");
    printf("3. Editar Gustos\n");
    printf("4. Buscar Personas\n");
    printf("5. Ver Lista de Favoritos\n");
    printf("6. Ver Lista de Matchs\n");
    printf("7. Bandeja de mensajes\n");
    printf("8. Top 10 personas\n");
    printf("9. Salir\n");
    printf("--------------------------------\n");
}

void menu(Red * total){

    impresionMenu();
    int opcion, opcion2;
    scanf("%d", &opcion);
    
    while(opcion != 0){
        switch(opcion){
        case 1:
            //ingresarPerfil();
            break;
        case 2: 
            //editarPerfil();
            break;
        case 3: 
            //EditarGustos();
            break;
        case 4:
            //BuscarPersonas();
            break;
        case 5:
            //ListFav();
            break;
        case 6:
            //ListMatch();
            break;
        case 7:
            //Mensajes();
            break;
        case 8:
            //Top10();
            break;
        case 9: 
            //cerrarSesion();
            break;
        default:
            printf("Ingrese una opcion valida\n-> ");
            scanf("%d", &opcion);
        }
        impresionMenu();
        printf("\nDesea realizar otra operacion?\n");
        printf("NO -> ingrese 0\n");
        printf("SI -> ingrese el numero de la operacion a realizar\n\ningrese su opcion: ");
        scanf("%d", &opcion);
        if(opcion == 0) break;
    }
}
   
Red *crearRed(){
    Red *usuario = (Red *) malloc(sizeof(Red));

    if(usuario == NULL){
        printf("No se pudo crear el usuario\n");
        return NULL;
    }

    usuario->totalUsuarios = createMap(is_equal_string);
    usuario->gustos = createMap(is_equal_string);
    usuario->cantidad = 0;

    return usuario;
}

usuario *crearUsuario(){
    usuario *aux = (usuario *) malloc(sizeof(usuario));
    aux->fav = createList();
    aux->match = createList();

    return aux;
}

void importar(FILE *archivo, Red* total)
{
    int i;
    char linea[1024];

    while (fgets(linea, 1024, archivo) != NULL)
    {
        linea[strcspn(linea, "\n")] = 0;

        usuario* AuxUsu = crearUsuario();
        AuxUsu->gustos = (tipoGustos *) malloc(sizeof(tipoGustos));
        
        for (int i = 0; i < 16; i++)
        {
            const char* aux = get_csv_field(linea, i);

            switch (i)
            {
                case 0:
                    strcpy(AuxUsu->nombre, aux);
                    break;
                case 1:
                    strcpy(AuxUsu->apodo, aux); 
                    break;
                case 2:
                    strcpy(AuxUsu->contrasena, aux);
                    break;
                case 3:
                    strcpy(AuxUsu->edad,aux);
                    break;
                case 4:
                    strcpy(AuxUsu->identidadG,aux);
                    break;
                case 5:
                    strcpy(AuxUsu->gustos->orientacionS,aux);
                    break;
                case 6:
                    strcpy(AuxUsu->gustos->generofav,aux);
                    break;
                case 7:
                    strcpy(AuxUsu->gustos->colorfav,aux);
                    break;
                case 8:
                    strcpy(AuxUsu->gustos->PelLib,aux);
                    break;
                case 9:
                    strcpy(AuxUsu->gustos->casaSalir,aux);
                    break;
                case 10:
                    strcpy(AuxUsu->gustos->estacionfav,aux);
                    break;
                case 11:
                    strcpy(AuxUsu->gustos->liqfav,aux);
                    break;
                case 12:
                    strcpy(AuxUsu->gustos->playaMontana,aux);
                    break;
                case 13:
                    strcpy(AuxUsu->gustos->depVid,aux);
                    break;
                case 14:
                    strcpy(AuxUsu->gustos->PerroGato,aux);
                    break;
                case 15:
                    strcpy(AuxUsu->gustos->comida,aux);
                    break;
            }
        }
        usuario *us = searchMap(total->totalUsuarios,AuxUsu->nombre);
        if(us == NULL){
            insertMap(total->totalUsuarios, AuxUsu->nombre,AuxUsu);
        }
    }
    fclose(archivo);
    printf("Archivo importado!\n\n");
}
