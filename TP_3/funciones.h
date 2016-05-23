#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "input.h"
typedef struct{
    char titulo[50];
    char genero[20];
    int duracion;
    char descripcion[100];
    int puntaje;
    char linkImagen[100];
    int isEmpty;
}EMovie;


int initArrayEstructuras(EMovie* pMovie, int length);
int cargarArchivo(EMovie *pMovie, int length);
int guardarEnArchivo(EMovie * pMovie, int length);
int buscarLibre(EMovie* pMovie, int length);
int buscarPorNombre(EMovie* pMovie, int length);
int pedirDatos(EMovie* pMovie, int length, char* titulo, char* genero, int* duracion, char* descripcion, int* puntaje, char* linkImagen, int primeraVez);
EMovie cargarDatos(char* titulo, char* genero, int* duracion, char* descripcion, int* puntaje, char* linkImagen);
int agregarPelicula(EMovie *pMovie, int length);
int borrarPelicula(EMovie* pMovie, int length);
int modificarPelicula(EMovie* pMovie, int length);
int escribirEnArchivo(FILE* pFile, char* texto);
char * leerArchivo(FILE* pFile);
void generarPagina(EMovie* pMovie, int length);

#endif // FUNCIONES_H_INCLUDED
