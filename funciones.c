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

    printf("\n\n                 Bienvenidx a SOCIAL MEET!\n-------------------------------------------------------\n\n");
    printf(" 1 -> Registrarse\n");
    printf(" 2 -> Iniciar sesion\n");
    printf(" 3 -> Salir de la app\n\n");
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
            printf("\n\n\n********** INICIO DE SESION *********\n\n");
            printf("Ingrese su nombre de usuario: ");
            getchar();
            scanf("%[^\n]s", nomUsuario);
            while(validarInfo(total->totalUsuarios, nomUsuario) == false){
                printf("El nombre de usuario es invalido, ingrese uno valido: ");
                getchar();
                scanf("%[^\n]s", nomUsuario);
                intento++;
                if(intento == 4){
                    printf("(!!) Demasiados intentos, lo redirigiremos al proceso de registro ...\n\n");
                    registrarUsuario(total);
                    return;
                }
            }
            intento = 0;
            printf("\nIngrese su contrasena: ");
            getchar();
            scanf("%[^\n]s", contUsuario);
            while(validarContrasena(total->totalUsuarios,nomUsuario,contUsuario) == false){
                printf("\n(!!) Contrasena incorrecta, ingrese nuevamente: ");
                getchar();
                scanf("%[^\n]s", contUsuario);
                intento++;
                if(intento == 4){
                    printf("\n(!!) Demasiados intentos, lo redirigiremos a la pagina principal ...\n");
                    ingresarApp(total);
                    return;
                }
            }

            strcpy(total->usuarioIngresado,nomUsuario);
            printf("\n-----------------------------------------\n");
            menu(total);
            break;
        case 3:
            printf("\nHa salido correctamente de la aplicacion! :D\n");
            return;
    }
}

void mostrarUsuario(usuario *usu){
    printf("----------------------------------------------------\n\n");
    printf("INFORMACION PRINCIPAL: \n\n");
    printf("NOMBRE               > %s\nAPODO                > %s\nCONTRASENA           > %s\nEDAD                 > %d\n", usu->nombre, usu->apodo, usu->contrasena, usu->edad);
    printf("IDENTIDAD SEXUAL     > %s\nORIENTACION SEXUAL   > %s\nINTENCION            > %s\n",usu->identidadG, usu->gustos->orientacionS, usu->intenciones);
    printf("\nGUSTOS: \n\n");
    printf("> genero musical favorito ----- %s\n",usu->gustos->generofav);
    printf("> color favorito -------------- %s\n",usu->gustos->colorfav);
    printf("> peliculas o libros ---------- %s\n",usu->gustos->PelLib);
    printf("> casa o salir ---------------- %s\n",usu->gustos->casaSalir);
    printf("> estacion favorita ----------- %s\n",usu->gustos->estacionfav);
    printf("> bebestible favorito --------- %s\n",usu->gustos->liqfav);
    printf("> playa o montana ------------- %s\n",usu->gustos->playaMontana);
    printf("> deportes o videojuegos ------ %s\n",usu->gustos->depVid);
    printf("> perros o gatos -------------- %s\n",usu->gustos->PerroGato);
    printf("> Dieta ----------------------- %s\n",usu->gustos->comida);
    printf("----------------------------------------------------\n\n\n\n\n");
}

void registrarUsuario(Red *total){
    usuario *new = crearUsuario();
    int edadU, identidad, intencion, orientacion, generoMus, color, PL, CS, estacion, bebestible, PM, DV, PG, dieta;
    char nomUsu[100],apodoU[100], contraU[100];

    printf("\n****************** REGISTRO ******************\n");
    printf("\n(!!) Advertencia: Asegurece de responder todas las \npreguntas y en el formato indicado\n\n");

    printf("-> Ingrese su nombre(s) y apellido(s) = ");
    getchar();
    scanf("%[^\n]s", nomUsu);
    while(validarInfo(total->totalUsuarios,nomUsu)){
        printf("\nEse nombre ya está registrado, ingrese otro: ");
        getchar();
        scanf("%[^\n]s",nomUsu);
    }
    
    strcpy(new->nombre,nomUsu);

    printf("\n-> Ingrese su nombre de usuario = ");
    getchar();
    scanf("%[^\n]s",apodoU);
    while(validarInfo(total->totalUsuarios, apodoU)){
        printf("\n(!!) Ese apodo ya esta registrado, ingrese otro: ");
        getchar();
        scanf("%[^\n]s",apodoU);
    }
    strcpy(new->apodo, apodoU);

    printf("\n-> Ingrese su contrasena, para mayor seguridad ingrese mas de 5 letras: ");
    getchar();
    scanf("%[^\n]s",contraU);
    while(strlen(contraU) < 5){
        printf("\n(!!) Minimo de caracteres no alcanzado, ingrese de nuevo su contrasena: ");
        getchar();
        scanf("%[^\n]s",contraU);
    }
    strcpy(new->contrasena,contraU);

    printf("\n(!!) Recuerde que debes ser mayor de 18 anyos para poder ocupar la aplicacion\n");
    printf("-> Ingrese su edad: ");
    scanf("%d", &edadU);
    if(edadU < 18){
        printf("\n(!!) No puede ingresar a la aplicacion\n");
        ingresarApp(total);
    }
    new->edad = edadU;

    printf("\n-> Ingrese la opcion con la cual se identifica:\n1. Masculino   2. Femenino  3.NoBinario\n");
    scanf("%d", &identidad);
    while(identidad < 1 || identidad > 3){
        printf("\n(!!) Ingrese una opcion valida\n");
        scanf("%d", &identidad);
    }
    switch(identidad){
        case 1:
            strcpy(new->identidadG,"masculino");
            break;
        case 2:
            strcpy(new->identidadG,"femenino");
            break;
        case 3:
            strcpy(new->identidadG,"nobinario");
            break;
    }

    printf("\n-> Ingrese la opcion para la cual utiliza la app:\n1. Buscar Amigos/as   2. Buscar Pareja  3. Encuentros casuales\n");
    scanf("%d", &intencion);
    while(intencion < 1 || intencion > 3){
        printf("\n(!!) Ingrese una opcion valida\n");
        scanf("%d", &intencion);
    }
    switch(identidad){
        case 1:
            strcpy(new->intenciones,"amigos");
            break;
        case 2:
            strcpy(new->intenciones,"pareja");
            break;
        case 3:
            strcpy(new->intenciones,"encuentro casual");
            break;
    }

    printf("(*) Seccion de gustos ----------------------------\n\n");
    printf("-> ¿Cual es su orientacion sexual?\n1. heterosexual  2. homosexual  3.bisexual  4.pansexual  5.asexual\n");
    scanf("%d", &orientacion);
    while(orientacion < 1 || orientacion > 5){
        printf("\n(!!) Ingrese una opcion valida: ");
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

    printf("-> Escoga entre estos generos musicales, su favorito:\n1. Rap  2. Rock  3.Pop  4. Electronica  5. Jazz  6.Reggaeton\n");
    scanf("%d", &generoMus);
    while(generoMus < 1 || generoMus > 6){
        printf("\n(!!) Ingrese una opcion valida: ");
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

    printf("-> Escoga entre estos colores, su favorito:\n1. Naranjo  2. Amarillo  3. Verde  4. Azul  5. Rojo  6. Morado\n");
    scanf("%d", &color);
    while(color < 1 || color > 6){
        printf("\n(!!) Ingrese una opcion valida: ");
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

    printf("-> Prefieres los libros o las peliculas?\n1. Libros  2. Peliculas\n");
    scanf("%d", &PL);
    while(PL < 1 || PL > 2){
        printf("\n(!!) Ingrese una opcion valida: ");
        scanf("%d", &PL);
    }
    if(PL == 1) strcpy(new->gustos->PelLib,"libros");
    else strcpy(new->gustos->PelLib,"peliculas");

    printf("-> Prefieres salir o quedarte en casa?\n1. Casa  2. Salir\n");
    scanf("%d", &CS);
    while(CS < 1 || CS > 2){
        printf("\n(!!) Ingrese una opcion valida: ");
        scanf("%d", &CS);
    }
    if(CS == 1) strcpy(new->gustos->casaSalir,"casa");
    else strcpy(new->gustos->casaSalir,"salir");

    printf("-> Cual estacion del anyo es tu favorita:\n1. Otono  2. Invierno  3. Primavera  4. Verano\n");
    scanf("%d", &estacion);
    while(estacion < 1 || estacion > 4){
        printf("\n(!!) Ingrese una opcion valida: ");
        scanf("%d", &estacion);
    }
    switch(estacion){
        case 1:
            strcpy(new->gustos->estacionfav, "otono");
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

    printf("-> De estas opciones de bebesitbles, cual es tu preferida:\n1. Te  2. Cafe  3. Bebida\n");
    scanf("%d", &bebestible);
    while(bebestible < 1 || bebestible > 3){
        printf("\n(!!) Ingrese una opcion valida: ");
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

    printf("-> Prefieres la playa o la montana:\n1. Playa  2.Montana\n");
    scanf("%d", &PM);
    while(PM < 1 || PM > 2){
        printf("\n(!!) Ingrese una opcion valida: ");
        scanf("%d", &PM);
    }
    if(PM == 1) strcpy(new->gustos->playaMontana,"playa");
    else strcpy(new->gustos->playaMontana,"montana");

    printf("-> Prefiers los deportes o los videojuegos:\n1. Deportes  2. Videojuegos\n");
    scanf("%d", &DV);
    while(DV < 1 || DV > 2){
        printf("\n(!!) Ingrese una opcion valida: ");
        scanf("%d", &DV);
    }
    if(DV == 1) strcpy(new->gustos->depVid,"deporte");
    else strcpy(new->gustos->depVid,"videojuegos");

    printf("-> Prefieres los perros o los gatos:\n1. Perros  2. Gatos\n");
    scanf("%d", &PG);
    while(PG < 1 || PG > 2){
        printf("\n(!!) Ingrese una opcion valida: ");
        scanf("%d", &DV);
    }
    if(PG == 1) strcpy(new->gustos->PerroGato,"perro");
    else strcpy(new->gustos->PerroGato,"gato");

    printf("-> De estas opciones, cual es tu dieta:\n1. Veganx  2. Vegetarianx  3. Carnivorx\n");
    scanf("%d", &dieta);
    while(dieta < 1 || dieta > 3){
        printf("\n(!!) Ingrese una opcion valida: ");
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
    total->cantidad++;
    printf("\n\n ** SU INFORMACION HA SIDO GUARDADA EXITOSAMENTE!\n");
    ingresarApp(total);
}

bool validarInfo(Map *mapa, char *key){
    usuario *buscado = searchMap(mapa,key);
    if(buscado == NULL) return false;
    return true;
}

bool validarContrasena(Map *total, char *nomUsuario, char *contUsuario){
    usuario *buscado = searchMap(total,nomUsuario);
    if(buscado != NULL){
        if(strcmp(contUsuario,buscado->contrasena) == 0) return true;
        else return false;
    }
    return false;
}

void calculo(Red *total, usuario *ingreso){
    usuario *indice = firstMap(total->totalUsuarios);
    while(indice != NULL){
        if(strcmp(indice->gustos->casaSalir,ingreso->gustos->casaSalir) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->colorfav,ingreso->gustos->colorfav) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->comida,ingreso->gustos->comida) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->depVid,ingreso->gustos->depVid) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->estacionfav,ingreso->gustos->estacionfav) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->generofav,ingreso->gustos->generofav) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->liqfav,ingreso->gustos->liqfav) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->orientacionS,ingreso->gustos->orientacionS) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->PelLib,ingreso->gustos->PelLib) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->PerroGato,ingreso->gustos->PerroGato) == 0) indice->compatibilidad += 1;
        if(strcmp(indice->gustos->playaMontana,ingreso->gustos->playaMontana) == 0) indice->compatibilidad += 1;
        indice = nextMap(total->totalUsuarios);
    }
}

void Compatibilidad(Red *total, int opcion, List *filtro){
    usuario *ingreso = searchMap(total->totalUsuarios,total->usuarioIngresado);
    if(ingreso == NULL){
        printf("Hubo un error, el usuario no se ingresó correctamente\n");
        menu(total);
    }

    calculo(total, ingreso);

    usuario *indice2 = firstMap(total->totalUsuarios);
    int opcionFav;
    if(opcion == 1){
        while(indice2 != NULL){
            if(indice2->compatibilidad >= 5 && (strcmp(indice2->apodo,ingreso->apodo) != 0)){
                pushFront(indice2->fav, ingreso);
                if(Filtrar(indice2, filtro) == true){
                    mostrarUsuario(indice2);
                    printf("> Desea agregar la persona a su lista de favoritos?\n1. SI  2. NO\n");
                    scanf("%d", &opcionFav);
                    while(opcionFav < 1 || opcionFav > 2){
                        printf("ingrese una opcion valida: ");
                        scanf("%d", &opcionFav);
                    }
                    if(opcionFav == 1){
                        pushBack(ingreso->fav, indice2);
                    }
                }
            }
            indice2 = nextMap(total->totalUsuarios);
        }
    }
    else{
        while(indice2 != NULL){
            if(indice2->compatibilidad <= 5 && (strcmp(indice2->apodo,ingreso->apodo) != 0)){
                pushFront(indice2->fav, ingreso);
                if(Filtrar(indice2, filtro) == true){
                    mostrarUsuario(indice2);
                    printf("> Desea agregar la persona a su lista de favoritos?\n1. SI  2. NO\n");
                    scanf("%d", &opcionFav);
                    while(opcionFav < 1 || opcionFav > 2){
                        printf("ingrese una opcion valida: ");
                        scanf("%d", &opcionFav);
                    }
                    if(opcionFav == 1){
                        pushBack(ingreso->fav, indice2);
                    }
                }
            }
            indice2 = nextMap(total->totalUsuarios);
        }
    }
}

bool Filtrar(usuario *fav, List *filtro){
    char ninguno[8] = "ninguno";
        int indice = 1;
        char *filtros = firstList(filtro);
        while(filtros != NULL){
            if(indice == 1){
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->generofav) != 0){
                        return false;
                    }
                }        
            }
            else if(indice == 2){
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->colorfav) != 0){
                        return false;
                    }
                }
            }
            else if(indice == 3){
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->PelLib) != 0){
                        return false;
                    }
                }
            }
            else if(indice == 4){
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->casaSalir) != 0){
                        return false;
                    }
                }
            }
            else if(indice == 5){
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->estacionfav) != 0){
                        return false;
                    }
                }
            }
            else if(indice == 6){
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->liqfav) != 0){
                        return false;
                    }
                }
            }
            else if(indice == 7){
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->playaMontana) != 0){
                        return false;
                    }
                }
            }
            else if(indice == 8){
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->depVid) != 0){
                        return false;
                    }
                }
            }
            else if(indice == 9){
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->PerroGato) != 0){
                        return false;
                    }
                }
            }
            else{
                if(strcmp(filtros,ninguno) != 0){
                    if(strcmp(filtros, fav->gustos->comida) != 0){
                        return false;
                    }
                }
            }
            indice++;
            filtros = nextList(filtro);
        }
    return true;
}

void ingresarFiltros(List *filtro){
    printf("> Preferencia gustos musicales:\n1. Rap  2. Rock  3. Pop 4. Electronica 5. Jazz  6. Reggaeton  7. Ninguno\n");
    int opcion;
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 7){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
            case 1:
                pushBack(filtro, "rap");
                break;
            case 2:
                pushBack(filtro, "rock");
                break;
            case 3:
                pushBack(filtro, "pop");
                break;
            case 4:
                pushBack(filtro, "electronica");
                break;
            case 5:
                pushBack(filtro, "jazz");
                break;
            case 6:
                pushBack(filtro, "reggaeton");
                break;
            case 7:
                pushBack(filtro, "ninguno");
                break;
        }

    printf("> Preferencia colores favoritos:\n1. Azul  2. Rojo  3. Morado 4. Amarillo 5. Naranjo  6. Verde  7. Ninguno\n");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 7){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
            case 1:
                pushBack(filtro, "azul");
                break;
            case 2:
                pushBack(filtro, "rojo");
                break;
            case 3:
                pushBack(filtro, "morado");
                break;
            case 4:
                pushBack(filtro, "amarillo");
                break;
            case 5:
                pushBack(filtro, "naranjo");
                break;
            case 6:
                pushBack(filtro, "verde");
                break;
            case 7:
                pushBack(filtro, "ninguno");
                break;
        }

    printf("> Preferencia peliculas o libros:\n1. Peliculas  2. Libros  3. Ninguno\n");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 3){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
            case 1:
                pushBack(filtro, "peliculas");
                break;
            case 2:
                pushBack(filtro, "libros");
                break;
            case 3:
                pushBack(filtro, "ninguno");
                break;
    }

    printf("> Preferencia quedarse en casa o salir:\n1. Quedarse en casa  2. Salir  3. Ninguno\n");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 3){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
            case 1:
                pushBack(filtro, "casa");
                break;
            case 2:
                pushBack(filtro, "salir");
                break;
            case 3:
                pushBack(filtro, "ninguno");
                break;
    }

    printf("> Preferencia estacion del anyo favorita:\n1. Verano  2. Invierno  3. Primavera  4. Otono  5. Ninguno\n");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 5){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
        case 1:
            pushBack(filtro, "verano");
            break;
        case 2:
            pushBack(filtro, "invierno");
            break;
        case 3:
            pushBack(filtro, "primavera");
            break;
        case 4:
            pushBack(filtro, "otono");
            break;
        case 5:
            pushBack(filtro, "ninguno");
            break;
    }

    printf("> Preferencia bebestible favorito:\n1. Te  2. Cafe  3. Bebida  4. Ninguno\n");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 4){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
        case 1:
            pushBack(filtro, "te");
            break;
        case 2:
            pushBack(filtro, "cafe");
            break;
        case 3:
            pushBack(filtro, "bebida");
            break;
        case 4:
            pushBack(filtro, "ninguno");
            break;
    }

    printf("> Preferencia ir a la playa o ir a las montanas:\n1. Playa  2. Montanas  3. Ninguno\n");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 3){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
            case 1:
                pushBack(filtro, "playa");
                break;
            case 2:
                pushBack(filtro, "motana");
                break;
            case 3:
                pushBack(filtro, "ninguno");
                break;
    }

    printf("> Preferencia entre hacer deporte o jugar videojuegos:\n1. Deporte  2. Videojuegos  3. Ninguno\n");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 3){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
            case 1:
                pushBack(filtro, "deporte");
                break;
            case 2:
                pushBack(filtro, "videojuegos");
                break;
            case 3:
                pushBack(filtro, "ninguno");
                break;
    }

    printf("> Preferencia entre los perros y los gatos:\n1. Perros  2. Gatos  3. Ninguno\n");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 3){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
            case 1:
                pushBack(filtro, "perro");
                break;
            case 2:
                pushBack(filtro, "gato");
                break;
            case 3:
                pushBack(filtro, "ninguno");
                break;
    }

    printf("> Preferencia en la dieta:\n1. Vegano  2. Vegetariano  3. Carnivoro  4. Ninguno\n");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 4){
        printf("ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    switch(opcion){
        case 1:
            pushBack(filtro, "vegano");
            break;
        case 2:
            pushBack(filtro, "vegetariano");
            break;
        case 3:
            pushBack(filtro, "carnivoro");
            break;
        case 4:
            pushBack(filtro, "ninguno");
            break;
    }
}

bool revisarListMatch(usuario *candidatos, char *apodo){
    usuario *indice = firstList(candidatos->fav);
    while(indice != NULL){
        if(strcmp(indice->apodo, apodo) == 0){
            pushBack(candidatos->match, indice);
            return true;
        }
    }
    return false;
}

void RevisarMatch(Red *total){
    usuario *registrado = searchMap(total->totalUsuarios, total->usuarioIngresado);
    usuario *candidatos = firstList(registrado->fav);
    while(candidatos != NULL){
        if(revisarListMatch(candidatos, registrado->apodo) == true){
            pushBack(registrado->match,candidatos);
            printf("Has hecho match con %s, enviale un mensaje!\n", candidatos->apodo);
        }
        candidatos = nextList(registrado->fav);
    }

}

int buscarMaxCompatible(Map *total){
    int maximo = 0;
    usuario *indice = firstMap(total);
    while(indice != NULL){
        if(indice->compatibilidad > maximo){
            maximo = indice->compatibilidad;
        }
        indice = nextMap(total);
    }
    return maximo;
}

void impresionMenu(){
    printf("\n\n\n\n\n*********** MENU **********\n\n");
    printf("1. Ingresar Perfil\n");
    printf("2. Editar Perfil\n");
    printf("3. Editar Gustos\n");
    printf("4. Buscar Personas\n");
    printf("5. Ver Lista de Favoritos\n");
    printf("6. Ver Lista de Matchs\n");
    printf("7. Bandeja de mensajes\n");
    printf("8. Top 10 personas\n");
    printf("9. Salir de la app\n");
    printf("--------------------------------\n");
}

void menu(Red * total){

    impresionMenu();
    int opcion, opcion2;
    printf("Ingrese la opcion que quiere realizar: ");
    scanf("%d", &opcion);
    printf("\n");

    while(opcion != 0){
        switch(opcion){
        case 1:
            ingresarPerfil(total);
            break;
        case 2: 
            editarPerfil(total);
            break;
        case 3: 
            EditarGustos(total);
            break;
        case 4:
            BuscarPersonas(total);
            break;
        case 5:
            ListFav(total);
            break;
        case 6:
            ListMatch(total);
            break;
        case 7:
            //Mensajes();
            break;
        case 8:
            Top10(total);
            break;
        case 9: 
            printf("\n\n****** Se ha cerrado correctamente la sesion, nos vemos! ******\n\n\n");
            return;
            
        default:
            printf("Ingrese una opcion valida\n-> ");
            scanf("%d", &opcion);
        }
        impresionMenu();
        printf("\nDesea realizar otra operacion?\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
    }
}

void ingresarPerfil(Red *total){
    usuario *buscado = searchMap(total->totalUsuarios,total->usuarioIngresado);
    if(buscado == NULL){
        printf("\n(!!) Ha ocurrido un error, no se puede ingresar al perfil\n");
        menu(total);
    }
    printf("********** INFORMACION USUARIO **********\n");
    mostrarUsuario(buscado);
}

void editarPerfil(Red *total){
    usuario *buscar = searchMap(total->totalUsuarios, total->usuarioIngresado);
    if(buscar == NULL){
        printf("Ha ocurrido un error, no se puede ingresar al perfil\n");
        menu(total);
    }

    int opcion, veces = 1, edadU, opcionI, opcionInt;
    char cambio[100];
    printf("Que gustos desea cambiar?:\n1. Nombre\n2. Nombre usuario\n3. Contrasena\n4. Identidad sexual\n5. Intenciones\n\n");
    printf("Ingrese su opcion: ");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 5){
        printf("\n(!!) Ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }

    switch(opcion){
        case 1:
            printf("\nIngrese el nombre para cambiar: ");
            getchar();
            scanf("%[^\n]s", cambio);
            while(validarInfo(total->totalUsuarios, cambio) == true){
                veces += 1;
                printf("\n(!!) Ese nombre ya esta registrado, ingrese otro: ");
                getchar();
                scanf("%[^\n]s", cambio);
                if(veces > 3){
                    printf("\n(!!) Demasiados intentos, volviendo al menu ...\n");
                    menu(total);
                }
            }
            strcpy(buscar->nombre,cambio);
            veces = 0;
            printf("\n\n*** SU NOMBRE HA SIDO CAMBIADO CON EXITO! ***\n\n\n");
            break;
        case 2:
            printf("\nIngrese su nuevo apodo (nombre usuario): ");
            getchar();
            scanf("%[^\n]s", cambio);
            while(validarInfo(total->totalUsuarios, cambio) == true){
                veces++;
                printf("\n(!!) Ese apodo ya esta registrado, ingrese otro: ");
                getchar();
                scanf("%[^\n]s", cambio);
                if(veces > 3){
                    printf("\n(!!) Demasiados intentos, volviendo al menu ...\n");
                    menu(total);
                }
            }
            strcpy(buscar->apodo,cambio);
            strcpy(total->usuarioIngresado,cambio);
            veces = 0;
            printf("\n\n*** SU NOMBRE DE USUARIO HA SIDO CAMBIADO CON EXITO! ***\n\n\n");
            break;
        case 3:
            printf("\n(!!) Advertencia: La nueva contrasena debe ser mayor a 5 caracteres\n");
            printf("Ingrese su nueva contrasena: ");
            getchar();
            scanf("%[^\n]s", cambio);
            while(strlen(cambio) < 5){
                printf("\n(!!) No cumple con las condiciones, ingrese nuevamente: ");
                getchar();
                scanf("%[^\n]s", cambio);
            }
            strcpy(buscar->contrasena,cambio);
            printf("\n\n*** SU CONTRASENA HA SIDO CAMBIADA CON EXITO! ***\n\n\n");
            break;
        case 4:
            printf("\n1. Mujer   2. Hombre   3. No Binario\n");
            printf("Ingrese la opcion para realizar el cambio: ");
            scanf("%d", &opcionI);
            while(opcionI < 1 || opcionI > 3){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &opcionI);
            }
            if(opcionI == 1) strcpy(buscar->identidadG,"mujer");
            if(opcionI == 2) strcpy(buscar->identidadG,"hombre");
            if(opcionI == 3) strcpy(buscar->identidadG,"nobinario");
            printf("\n\n*** SU IDENTIDAD HA SIDO CAMBIADO CON EXITO ***\n\n\n");
            break;
        case 5:
            printf("\n1. Amigos/as   2. Pareja   3. Encuentro Casual\n");
            printf("Ingrese la opcion para realizar el cambio: ");
            scanf("%d", &opcionInt);
            while(opcionInt < 1 || opcionInt > 3){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &opcionI);
            }
            if(opcionInt == 1) strcpy(buscar->intenciones,"amigos");
            if(opcionInt == 2) strcpy(buscar->intenciones,"pareja");
            if(opcionInt == 3) strcpy(buscar->intenciones,"encuentro casual");
            printf("\n\n*** SU INTENCION HA SIDO CAMBIADO CON EXITO ***\n\n\n");
            break;
    }
}

void EditarGustos(Red *total){
    usuario *buscar = searchMap(total->totalUsuarios, total->usuarioIngresado);
    if(buscar == NULL){
        printf("Ha ocurrido un error, no se puede ingresar al perfil\n");
        menu(total);
    }
    int opcion, cambio;
    printf("Que gustos desea cambiar?:\n1. orientacion sexual\n2.genero musical favorito\n3.color favorito\n4.peliculas/salir\n5.estacion favorita\n6.bebestible\n7.playa/montana\n8.deporte/videojuegos\n9.perros/gatos\n10.dieta\n");
    printf("Ingrese su opcion: ");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 10){
        printf("\n(!!) Ingrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    printf("\n");
    switch(opcion){
        case 1:
            printf("Escoga entre las opciones, para cambiar su ORIENTACION SEXUAL:\n1. heterosexual\n2. homosexual\n3. bisexual\n4. pansexual\n5. asexual\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 5){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->orientacionS,"heterosexual");
            if(cambio == 2) strcpy(buscar->gustos->orientacionS,"homosexual");
            if(cambio == 3) strcpy(buscar->gustos->orientacionS,"bisexual");
            if(cambio == 4) strcpy(buscar->gustos->orientacionS,"pansexual");
            if(cambio == 5) strcpy(buscar->gustos->orientacionS,"asexual");
            break;
        case 2:
            printf("Escoga entre las opciones, para cambiar su GENERO MUSICAL FAVORITO:\n1. rap\n2. rock\n3. pop\n4. electronica\n5. jazz\n6. reggaeton\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 6){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->generofav,"rap");
            if(cambio == 2) strcpy(buscar->gustos->generofav,"rock");
            if(cambio == 3) strcpy(buscar->gustos->generofav,"pop");
            if(cambio == 4) strcpy(buscar->gustos->generofav,"electronica");
            if(cambio == 5) strcpy(buscar->gustos->generofav,"jazz");
            if(cambio == 6) strcpy(buscar->gustos->generofav,"reggaeton");
            break;
        case 3:
            printf("Escoga entre las opciones, para cambiar su COLOR FAVORITO:\n1. naranjo\n2. amarillo\n3. verde\n4. azul\n5. rojo\n6. morado\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 6){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->colorfav,"naranjo");
            if(cambio == 2) strcpy(buscar->gustos->colorfav,"amarillo");
            if(cambio == 3) strcpy(buscar->gustos->colorfav,"verde");
            if(cambio == 4) strcpy(buscar->gustos->colorfav,"azul");
            if(cambio == 5) strcpy(buscar->gustos->colorfav,"rojo");
            if(cambio == 6) strcpy(buscar->gustos->colorfav,"morado");
            break;
        case 4:
            printf("Escoga entre las opciones, para cambiar su PREFERENCIA:\n1. Casa\n2. Salir\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 2){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->casaSalir,"casa");
            if(cambio == 2) strcpy(buscar->gustos->casaSalir,"salir");
            break;
        case 5:
            printf("Escoga entre las opciones, para cambiar su ESTACION DEL ANYO FAVORITA:\n1. Verano\n2. Invierno\n3. Primavera\n4. Otono\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 4){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->estacionfav,"verano");
            if(cambio == 2) strcpy(buscar->gustos->estacionfav,"invierno");
            if(cambio == 3) strcpy(buscar->gustos->estacionfav,"primavera");
            if(cambio == 4) strcpy(buscar->gustos->estacionfav,"otono");
            break;
        case 6:
            printf("Escoga entre las opciones, para cambiar su BEBESTIBLE FAVORITO:\n1. Te\n2. Cafe\n3. Bebida\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 3){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->liqfav,"te");
            if(cambio == 2) strcpy(buscar->gustos->liqfav,"cafe");
            if(cambio == 3) strcpy(buscar->gustos->liqfav,"bebida");
            break;
        case 7:
            printf("Escoga entre las opciones, para cambiar su PREFERENCIA:\n1. Playa\n2. Montana\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 2){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->playaMontana,"playa");
            if(cambio == 2) strcpy(buscar->gustos->playaMontana,"montana");
            break;
        case 8:
            printf("Escoga entre las opciones, para cambiar su PREFERENCIA:\n1. Deporte\n2. Videojuegos\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 2){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->depVid,"deporte");
            if(cambio == 2) strcpy(buscar->gustos->depVid,"videojuegos");
            break;
        case 9:
            printf("Escoga entre las opciones, para cambiar su PREFERENCIA:\n1. Perros\n2. Gatos\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 2){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->PerroGato,"perro");
            if(cambio == 2) strcpy(buscar->gustos->PerroGato,"gato");
            break;
        case 10:
            printf("Escoga entre las opciones, para cambiar su DIETA:\n1. Vegetariano\n2. Carnivoro\n3. Vegano\n");
            printf("Ingrese aqui: ");
            scanf("%d", &cambio);
            while(cambio < 1 || cambio > 3){
                printf("\n(!!) Ingrese una opcion valida: ");
                scanf("%d", &cambio);
            }
            if(cambio == 1) strcpy(buscar->gustos->comida,"vegetariano");
            if(cambio == 2) strcpy(buscar->gustos->comida,"carnivoro");
            if(cambio == 3) strcpy(buscar->gustos->comida,"vegano");
            break;
    }
    mostrarUsuario(buscar);
}

void BuscarPersonas(Red *total){
    int opcion;
    printf("Desea buscar personas similares a usted, o diferentes?\n1. Similares  2. Distintos\n\nIngrese su opcion: ");
    scanf("%d", &opcion);
    while(opcion < 1 || opcion > 2){
        printf("Opcion invalida, ingrese nuevamente la operacion a realizar: ");
        scanf("%d", &opcion);
    }
    List *filtro = createList();
    printf("\n     SECCION FILTRO\n--------------------\n\n");
    printf("(!!) En esta seccion podras seleccionar ciertos aspectos que puedes \nseleccionar para una busqueda mas eficas y especifica\n\n");
    ingresarFiltros(filtro);
    if(opcion == 1){
        Compatibilidad(total, opcion, filtro);
    }

    else{
        Compatibilidad(total, opcion, filtro);
    }

    RevisarMatch(total);
    // Aquí revisamos si se hizo un match :p
    /* La idea es recorrer la lista de fav del usuario que ingreso, buscamos aquellas personas en el mapa y revisamos su lista de fav
    si el usuario está, lo ingresamos a la lista de match, si el usuario ingresa a la opcion de ver lista de match, inciamos la conversacion,
    cosa que cuando entre a la bandeja de mensajes, se muestre el mapa, es decir el nombre de la persona y los mensajes.*/



}

void ListFav(Red *total){
    usuario *ingresado = searchMap(total->totalUsuarios, total->usuarioIngresado);
    usuario *candidatos = firstList(ingresado->fav);
    int opcion;
    if(candidatos == NULL){
        printf("Aun no has guardado a nadie en tu lista\n");
    }
    else{
        while(candidatos != NULL){
            mostrarUsuario(candidatos);
            printf("Deseas eliminar al usuario?\n1. SI  2. NO\n");
            scanf("%d", &opcion);
            while(opcion < 1 || opcion > 2){
                printf("Ingrese una opcion valida: ");
                scanf("%d", &opcion);
            }
            if(opcion == 1){
                popCurrent(ingresado->fav);
            }
            candidatos = nextList(ingresado->fav);
        }        
    }
}

void ListMatch(Red *total){
    usuario *ingreso = searchMap(total->totalUsuarios, total->usuarioIngresado);
    usuario *candidato = firstList(ingreso->match);
    if(candidato == NULL){
        printf("Aun no has hecho match con ninguna persona :c\n");
    }
    else{
        while(candidato != NULL){
            mostrarUsuario(candidato);
            candidato = nextList(ingreso->match);
        }
    }
}

void Top10(Red *total){
    usuario *ingreso = searchMap(total->totalUsuarios, total->usuarioIngresado);
    calculo(total,ingreso);
    usuario *indice = firstMap(total->totalUsuarios);
    List *lista = createList();
    int maximo = buscarMaxCompatible(total->totalUsuarios);
    int contador = 1;

    /*while(indice != NULL){
        if(indice->compatibilidad == maximo  && contador <= 10){
            mostrarUsuario(indice);
            pushBack(lista,indice);
            contador++;
        }
        indice = nextMap(total->totalUsuarios);
    }

    usuario *indList = firstList(lista);
    if(indList == NULL){
        printf("No hay ninguna coincidencia con ningun usuario :C\n");
    }
    else{
        while(indList != NULL){
            mostrarUsuario(indList);
            indList = nextList(lista);
        }
    }*/
}
   
Red *crearRed(){
    Red *usuario = (Red *) malloc(sizeof(Red));

    if(usuario == NULL){
        printf("No se pudo crear el usuario\n");
        return NULL;
    }

    usuario->totalUsuarios = createMap(is_equal_string);
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
        
        for (int i = 0; i < 17; i++)
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
                    strcpy(AuxUsu->identidadG, aux);
                    break;
                case 5:
                    strcpy(AuxUsu->intenciones, aux);
                    break;
                case 6:
                    strcpy(AuxUsu->gustos->orientacionS, aux);
                    break;
                case 7:
                    strcpy(AuxUsu->gustos->generofav, aux);
                    break;
                case 8:
                    strcpy(AuxUsu->gustos->colorfav, aux);
                    break;
                case 9:
                    strcpy(AuxUsu->gustos->PelLib, aux);
                    break;
                case 10:
                    strcpy(AuxUsu->gustos->casaSalir, aux);
                    break;
                case 11:
                    strcpy(AuxUsu->gustos->estacionfav, aux);
                    break;
                case 12:
                    strcpy(AuxUsu->gustos->liqfav, aux);
                    break;
                case 13:
                    strcpy(AuxUsu->gustos->playaMontana, aux);
                    break;
                case 14:
                    strcpy(AuxUsu->gustos->depVid, aux);
                    break;
                case 15:
                    strcpy(AuxUsu->gustos->PerroGato, aux);
                    break;
                case 16:
                    strcpy(AuxUsu->gustos->comida, aux);
                    break;
            }
        }
        
        usuario *us = searchMap(total->totalUsuarios,AuxUsu->nombre);
        if(us == NULL){
            insertMap(total->totalUsuarios, AuxUsu->apodo,AuxUsu);
        }
    }
    fclose(archivo);
}