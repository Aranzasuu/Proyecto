#ifndef funciones_h
#define funciones_h 
#include <stdbool.h>
#include "list.h"
#include "Map.h"

typedef struct tipoGustos{ 
    char orientacionS[100];      //* 
    char generofav[100];         //* genero musical favorito (5)
    char colorfav[100];          //color favorito
    char PelLib[100];            //Pelicula o libro
    char casaSalir[100];         //* Quedarse en casa o salir
    char estacionfav[100];       //
    char liqfav[100];
    char playaMontana[100];
    char depVid[100];
    char PerroGato[100];
    char comida[100];            //vegano, vegetariano, carnívoro
} tipoGustos;

typedef struct usuario{
    char nombre[100];
    char apodo[100];
    char contrasena[100];
    int edad;
    char identidadG[100];          // arreglar la identidad, a: masculino, femenino, no binario :p
    char intenciones[100];         // amigxs, pareja, encuentro intimo
    tipoGustos *gustos;
    List *fav;
    List *match;
    Map *chat;
    int compatibilidad;
} usuario;

typedef struct Red{
    Map *totalUsuarios;
    int cantidad;
    char usuarioIngresado[100];
} Red;

int is_equal_string(void * key1, void * key2);
const char *get_csv_field (char * tmp, int k);

void mostrarUsuario(usuario *usu);
void mostrarMapa(Map *totalUsuarios);

void importar(FILE *archivo, Red *total);
Red *crearRed();
usuario *crearUsuario();
void ingresarApp(Red *total);
void impresionMenu();
void registrarUsuario(Red *total);
void menu(Red *total);

void ingresarPerfil(Red *total);
void editarPerfil(Red *total);
void EditarGustos(Red *total);
void BuscarPersonas(Red *total);
void ListFav(Red *total);
void ListMatch(Red *total);
void Top10(Red *total);

bool validarInfo(Map *mapa, char *key);
bool validarContrasena(Map *totalUsuarios, char *nomUsuario, char *contUsuario);
void calculo(Red *total, usuario *ingreso);
void Compatibilidad(Red *total, int opcion, List *filtro);
void ingresarFiltros(List *filtro);
bool Filtrar(usuario *fav, List *filtro);
void RevisarMatch(Red *total);
bool revisarListMatch(usuario *candidatos, char *apodo);

#endif