#ifndef funciones_h
#define funciones_h 
#include <stdbool.h>
#include "list.h"
#include "Map.h"

typedef struct tipoGustos{ 
    char orientacionS[100];  //* 
    char *generofav;    //* genero musical favorito (5)
    char *colorfav;     //color favorito
    char *PelLib;       //Pelicula o libro
    char *casaSalir;    //* Quedarse en casa o salir
    char *estacionfav;  //
    char *liqfav;
    char *playaMontana;
    char *depVid;
    char *PerroGato;
    char *comida;      //vegano, vegetariano, carnívoro
} tipoGustos;

typedef struct usuario{
    char nombre[100];
    char apodo[100];
    char contrasena[100];
    char edad[3];
    char identidadG[100];
    tipoGustos *gustos;
    List *fav;
    List *match;
    Map *chat;
} usuario;

typedef struct Red{
    Map *totalUsuarios;
    Map *gustos;
    int cantidad;
} Red;

int is_equal_string(void * key1, void * key2);
const char *get_csv_field (char * tmp, int k);

void mostrarMapa(Red *total);

void importar(FILE *archivo, Red *total);
Red *crearRed();
void ingresarApp(Red *total);
void impresionMenu();
bool validarUsuario(Red *total, char *nombreUsu, char *contrasenaUsu);
void registrarUsuario(Red *total);
void menu(Red *total);

#endif