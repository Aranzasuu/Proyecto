#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "list.h"
#include "funciones.h"

int is_equal_string(void * key1, void * key2) 
{
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

void ingresarApp(Red *total){
    int opcion, opcion2;
    char nombreUsu[100], contrasenaUsu[100];
    printf(" 1 -> Registrarse\n");
    printf(" 2 -> Iniciar sesion\n");
    printf(" 3 -> Salir\n");
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
        if(validarUsuario(total, nombreUsu, contrasenaUsu)) menu();
        else 
        {
            printf("Usuario invalido\n");
            printf("Desea volver a ingresar?\n");
            printf("1. SI         2.NO\n");
            scanf("%d", &opcion2);
            if(opcion2 == 1){
                while(validarUsuario(total, nombreUsu, contrasenaUsu) == false){
                    printf("Usuario invalido\n");
                    printf("Desea volver a ingresar?\n");
                    printf("1. SI         2.NO      3. Registrase\n");
                    scanf("%d", &opcion2);
                    if(opcion2 == 1){
                        printf("Ingrese el nombre de usuario: ");
                        scanf("%[^\n]s", nombreUsu);
                        printf("\nIngrese la contraseña: ");
                        scanf("%[^\n]s", contrasenaUsu);
                    }
                    if(opcion2 == 2) return;
                    if (opcion2 == 3){
                        registrarUsuario(total);
                        return;
                    }
                }
            }
        }
    }
    if(opcion == 3){
        printf("Ha salido de la aplicacion\n");
        return;
    }
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

void menu(){

    impresionMenu();
    int opcion, opcion2;
    scanf("%d", &opcion);
    
    while(opcion != 0){
        switch(opcion){
        case 1:
            ingresarPerfil();
            break;
        case 2: 
            editarPerfil();
            break;
        case 3: 
            EditarGustos();
            break;
        case 4:
            BuscarPersonas();
            break;
        case 5:
            ListFav();
            break;
        case 6:
            ListMatch();
            break;
        case 7:
            Mensajes();
            break;
        case 8:
            Top10();
            break;
        case 9: 
            cerrarSesion();
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
    return 0;
}
   
Red *crearRed(){
    Red *usuario = (Red *) malloc(sizeof(Red));

    if(usuario == NULL){
        printf("No se creo el usuario\n");
        return NULL;
    }

    usuario->cantidad = createMap(is_equal_string);
    usuario->gustos = createMap(is_equal_string);
    usuario->cantidad = 0;
    
    usuario = 0;

    return usuario;
}

usuario *crearUsuario(){
  usuario *aux = (usuario *) malloc(sizeof(usuario));
  aux->edad = 0;
}

void importar(FILE *archivo, Red* totalUsuarios)
{
    int i;
    char linea[1024];

    while (fgets(linea, 1024, archivo) != NULL)
    {
        linea[strcspn(linea, "\n")] = 0;

        usuario* AuxUsu = crearUsuario();
        tipoGustos* auxgus = crearGustos();
        
        for (int i = 0; i < 5; i++)
        {
            const char* aux = get_csv_field(linea, i);

            switch (i)
            {
                case 0:
                    strcpy(AuxUsu, aux);
                    break;
                case 1:
                    strcpy(AuxUsu, aux); 
                    break;
                case 2:
                    strcpy(AuxUsu, aux);
                    break;
    
            }
        }
        
    }
    fclose(archivo);
    printf("Archivo importado!\n\n");
}
