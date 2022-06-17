#ifndef funciones_h
#define funciones_h 
#include "list.h"

typedef struct usuario{
    char nombre[100];
    char apodo[100];
    char contrasena[100];
    int edad;
    char identidadG[100];
    tipoGustos *gustos;
    List *fav;
    List *match;
    //pila de mensajes del usuario;
} usuario;

typedef struct tipoGustos{ 
    char orientacionS[100];  //* 
    char *generofav;    //* genero musical favorito (5)
    char *colorfav;     //color favorito
    char *PelLib;       //Pelicula o libro
    char *casaSalir;    //* Quedarse en casa o salir
    char *estacionfav;  //
    char *liqfav;
    char *depVid;
    char *PerroGato;
    char *comida;      //vegano, vegetariano, carnívoro
} tipoGustos;

typedef struct red{
    Map *totalUsuarios;
    Map *gustos;
    int cantidad;
} red;

void ingresarApp(Red *total);
void impresionMenu();
bool validarUsuario(Red *total, char *nombreUsu, char *contraseñaUsu);
void registrarUsuario(Red *total);

#endif