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

void ingresarApp(Red *total)
{
    int opcion, intento = 0;
    char nomUsuario[100], contUsuario[100];

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

    switch(opcion){
        case 1:
            registrarUsuario(total);
            break;
        case 2:
            printf("ingrese su nombre de usuario: ");
            getchar();
            scanf("%[^\n]s", nomUsuario);
            while(validarUsuario(total->totalUsuarios, nomUsuario) == false){
                printf("El nombre de usuario es invalido, ingrese uno valido: ");
                getchar();
                scanf("%[^\n]s", nomUsuario);
                intento++;
                if(intento == 4){
                    printf("Demasiados intentos, lo redirigiremos al proceso de registro ...\n");
                    registrarUsuario(total);
                    return;
                }
            }
            intento = 0;
            printf("ingrese su contraseña: ");
            getchar();
            scanf("%[^\n]s", contUsuario);
            while(validarContrasena(total->totalUsuarios,nomUsuario,contUsuario) == false){
                printf("Contraseña incorrecta, ingrese nuevamente: ");
                getchar();
                scanf("%[^\n]s", contUsuario);
                intento++;
                if(intento == 4){
                    printf("Demasiados intentos, lo ressirigiremos a la pagina principal ...\n");
                    ingresarApp(total);
                    return;
                }
            }

            strcpy(total->usuarioIngresado,nomUsuario);
            menu(total);
            break;
        case 3:
            printf("Ha salido correctamente de la aplicacion! :D\n");
            return;
    }
}

void mostrarMapa(Map *totalUsuarios){
    usuario *unitario = firstMap(totalUsuarios);
    while(unitario != NULL){
        mostrarUsuario(unitario);
        unitario = nextMap(totalUsuarios);
    }
}

void mostrarUsuario(usuario *usu){
    printf("----------------------------------------------------\n\n");
    printf("nombre = %s\n", usu->nombre);
    printf("apodo = %s\n",usu->apodo);
    printf("contrasena = %s\n",usu->contrasena);
    printf("edad = %d\n",usu->edad);
    printf("identidad sexual = %s\n",usu->identidadG);
    printf("orientacion sexual = %s\n",usu->gustos->orientacionS);
    printf("genero musical fav = %s\n",usu->gustos->generofav);
    printf("color fav = %s\n",usu->gustos->colorfav);
    printf("peli o libros = %s\n",usu->gustos->PelLib);
    printf("casa o salir = %s\n",usu->gustos->casaSalir);
    printf("estacion fav = %s\n",usu->gustos->estacionfav);
    printf("bebestible fav = %s\n",usu->gustos->liqfav);
    printf("playa o montana = %s\n",usu->gustos->playaMontana);
    printf("dep o vid = %s\n",usu->gustos->depVid);
    printf("perro o gato = %s\n",usu->gustos->PerroGato);
    printf("comida = %s\n",usu->gustos->comida);
    printf("----------------------------------------------------\n\n");
}

void registrarUsuario(Red *total){
    usuario *new = crearUsuario();
    int edadU, identidad, orientacion, generoMus, color, CS, estacion, bebestible, PM, DV, PG, dieta;
    char nomUsu[100],apodoU[100], contraU[100];

    printf("**************** REGISTRO ****************");
    printf("Advertencia: Asegurece de responder todas las preguntas y en el formato indicado\n");

    printf("Ingrese su primer nombre y primer apellido = ");
    getchar();
    scanf("%[^\n]s", nomUsu);
    while(validarRepeticiones(total->totalUsuarios,nomUsu)){
        printf("Ese nombre ya está registrado, ingrese otro: ");
        getchar();
        scanf("%[^\n]s",nomUsu);
    }
    strcpy(new->nombre,nomUsu);

    printf("\nIngrese su nombre de usuario = ");
    getchar();
    scanf("%[^\n]s",apodoU);
    while(validarRepeticiones(total->totalUsuarios, apodoU)){
        printf("Ese apodo ya esta registrado, ingrese otro: ");
        getchar();
        scanf("%[^\n]s",apodoU);
    }
    strcpy(new->apodo,apodoU);

    printf("Ingrese su contraseña, para mayor seguridad ingrese mas de 5 letras: ");
    getchar();
    scanf("%[^\n]s",contraU);
    while(strlen(contraU) < 5){
        printf("minimo de caracteres no alcanzado, ingrese de nuevo su contraseña: ");
        getchar();
        scanf("%[^\n]s",contraU);
    }
    strcpy(new->contrasena,contraU);

    printf("(!!) recuerde que debes ser mayor de 18 años para poder ocupar la aplicacion\n");
    printf("ingrese su edad: ");
    scanf("%d", &edadU);
    if(edadU < 18){
        printf("no puede ingresar a la aplicacion\n");
        ingresarApp(total);
    }

    printf("ingrese la opcion con la cual se identifica:\n1. Masculino   2. Femenino  3.NoBinario\n");
    scanf("%d", &identidad);
    while(identidad < 1 || identidad > 3){
        printf("Ingrese una opcion valida\n");
        scanf("%d", &identidad);
    }
    switch(identidad){
        case 1:
            strcpy(new->identidadG,"Masculino");
            break;
        case 2:
            strcpy(new->identidadG,"Femenino");
            break;
        case 3:
            strcpy(new->identidadG,"NoBinario");
            break;
    }

    printf("(*) Seccion de gustos -------------------------\n\n");
    printf("a) ¿Cual es su orientacion sexual?\n1. heterosexual  2. homosexual  3.bisexual  4.pansexual  5.asexual\n");
    scanf("%d", &orientacion);
    while(orientacion < 1 || orientacion > 5){
        printf("ingrese una opcion valida: ");
        scanf("%d", &orientacion);
    }
    switch(orientacion){
        case 1:
            strcpy(new->gustos->orientacionS,"heterosexual");
            break;
        case 2:
            strcpy(new->gustos->orientacionS,"homosexual");
            break;
        case 3:
            strcpy(new->gustos->orientacionS,"bisexual");
            break;
        case 4:
            strcpy(new->gustos->orientacionS,"pansexual");
            break;
        case 5:
            strcpy(new->gustos->orientacionS,"asexual");
            break;
    }

    printf("b) Escoga entre estos generos musicales, su favorito:\n1. Rap  2. Rock  3.Pop  4. Electronica  5. Jazz  6.Reggaeton\n");
    scanf("%d", &generoMus);
    while(generoMus < 1 || generoMus > 6){
        printf("ingrese una opcion valida: ");
        scanf("%d", &generoMus);
    }
    switch(generoMus){
        case 1:
            strcpy(new->gustos->generofav, "rap");
            break;
        case 2:
            strcpy(new->gustos->generofav, "rock");
            break;
        case 3:
            strcpy(new->gustos->generofav, "pop");
            break;
        case 4:
            strcpy(new->gustos->generofav, "electronica");
            break;
        case 5:
            strcpy(new->gustos->generofav, "jazz");
            break;
        case 6:
            strcpy(new->gustos->generofav, "reggaeton");
            break;
    }

    printf("c) Escoga entre estos colores, su favorito:\n1. Naranjo  2. Amarillo  3. Verde  4. Azul  5. Rojo  6. Morado\n");
    scanf("%d", &color);
    while(color < 1 || color > 6){
        printf("ingrese una opcion valida: ");
        scanf("%d", &color);
    }
    switch(color){
        case 1:
            strcpy(new->gustos->colorfav, "naranjo");
            break;
        case 2:
            strcpy(new->gustos->colorfav, "amarillo");
            break;
        case 3:
            strcpy(new->gustos->colorfav, "verde");
            break;
        case 4:
            strcpy(new->gustos->colorfav, "azul");
            break;
        case 5:
            strcpy(new->gustos->colorfav, "rojo");
            break;
        case 6:
            strcpy(new->gustos->colorfav, "morada");
            break;
    }

    printf("d) Prefieres salir o quedarte en casa?\n1. Casa  2. Salir\n");
    scanf("%d", &CS);
    while(CS < 1 || CS > 2){
        printf("ingrese una opcion valida: ");
        scanf("%d", &CS);
    }
    if(CS == 1) strcpy(new->gustos->casaSalir,"casa");
    else strcpy(new->gustos->casaSalir,"salir");

    printf("e) Cual estacion del año es tu favorita:\n1. Otoño  2. Invierno  3. Primavera  4. Verano\n");
    scanf("%d", &estacion);
    while(estacion < 1 || estacion > 4){
        printf("ingrese una opcion valida: ");
        scanf("%d", &estacion);
    }
    switch(estacion){
        case 1:
            strcpy(new->gustos->estacionfav, "otoño");
            break;
        case 2:
            strcpy(new->gustos->estacionfav, "invierno");
            break;
        case 3:
            strcpy(new->gustos->estacionfav, "primavera");
            break;
        case 4:
            strcpy(new->gustos->estacionfav, "verano");
            break;
    }

    printf("f) De estas opciones de bebesitbles, cual es tu preferida:\n1. Te  2. Cafe  3. Bebida\n");
    scanf("%d", &bebestible);
    while(bebestible < 1 || bebestible > 3){
        printf("ingrese una opcion valida: ");
        scanf("%d", &bebestible);
    }
    switch(bebestible){
        case 1:
            strcpy(new->gustos->liqfav, "te");
            break;
        case 2:
            strcpy(new->gustos->liqfav, "cafe");
            break;
        case 3:
            strcpy(new->gustos->liqfav, "bebida");
            break;
    }

    printf("g) Prefieres la playa o la montaña:\n1. Playa  2.Montaña\n");
    scanf("%d", &PM);
    while(PM < 1 || PM > 2){
        printf("ingrese una opcion valida: ");
        scanf("%d", &PM);
    }
    if(PM == 1) strcpy(new->gustos->playaMontana,"playa");
    else strcpy(new->gustos->playaMontana,"montana");

    printf("h) Prefiers los deportes o los videojuegos:\n1. Deportes  2. Videojuegos\n");
    scanf("%d", &DV);
    while(DV < 1 || DV > 2){
        printf("ingrese una opcion valida: ");
        scanf("%d", &DV);
    }
    if(DV == 1) strcpy(new->gustos->depVid,"deporte");
    else strcpy(new->gustos->depVid,"videojuegos");

    printf("i) Prefieres los perros o los gatos:\n1. Perros  2. Gatos\n");
    scanf("%d", &PG);
    while(PG < 1 || PG > 2){
        printf("ingrese una opcion valida: ");
        scanf("%d", &DV);
    }
    if(PG == 1) strcpy(new->gustos->PerroGato,"perro");
    else strcpy(new->gustos->PerroGato,"gato");

    printf("De estas opciones, cual es tu dieta:\n1. Veganx  2. Vegetarianx  3. Carnivorx\n");
    scanf("%d", &dieta);
    while(dieta < 1 || dieta > 3){
        printf("ingrese una opcion valida: ");
        scanf("%d", &dieta);
    }
    switch(dieta){
        case 1:
            strcpy(new->gustos->comida, "vegano");
            break;
        case 2:
            strcpy(new->gustos->comida, "vegetariano");
            break;
        case 3:
            strcpy(new->gustos->comida, "carnivoro");
            break;
    }

    insertMap(total->totalUsuarios,new->apodo,new);
    printf("SU INFORMACION HA SIDO GUARDADA EXITOSAMENTE!\n");
    ingresarApp(total);
}

bool validarRepeticiones(Map *mapa, char *key){
    usuario *buscado = searchMap(mapa,key);
    if(buscado == NULL) return false;
    return true;
}

bool validarUsuario(Map *total, char *nombreU){
    usuario *aux = searchMap(total, nombreU);
    if(aux == NULL) return false;
    return true;
    /*while(aux != NULL){
        if(strcmp(nombreU,aux->nombre)) return true;
        aux = nextMap(total->totalUsuarios);
    }
    return false;*/
}

bool validarContrasena(Map *total, char *nomUsuario, char *contUsuario){
    return true;
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
            ingresarPerfil(total);
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
            printf("\n\n****** Se ha cerrado correctamente la aplicacion, nos vemos! ******\n\n\n");
            return;
            
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

void ingresarPerfil(Red *total){
    usuario *buscado = searchMap(total->totalUsuarios,total->usuarioIngresado);
    mostrarUsuario(buscado);
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
    aux->gustos = (tipoGustos *) malloc(sizeof(tipoGustos));
    aux->fav = createList();
    aux->match = createList();
    aux->compatibilidad = 0;

    return aux;
}

void importar(FILE *archivo, Red* total)
{
    int i,num;
    char *ptr;
    char linea[100024];

    while (fgets(linea, 100024, archivo) != NULL)
    {
        linea[strcspn(linea, "\n")] = 0;

        usuario* AuxUsu = crearUsuario();
        
        for (int i = 0; i < 16; i++)
        {
            const char* aux = get_csv_field(linea, i);
            total->cantidad++;

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
                    num = strtol(aux,&ptr,10);
                    AuxUsu->edad = num;
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
            insertMap(total->totalUsuarios, AuxUsu->apodo,AuxUsu);
        }
    }
    //mostrarMapa(total->totalUsuarios);
    fclose(archivo);
}
