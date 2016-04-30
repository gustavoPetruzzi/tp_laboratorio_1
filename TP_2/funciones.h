#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct {

    char nombre[50];
    int edad;
    int dni;
    int estado; // si esta en 0, esta vacio. Si esta en 1, esta lleno.

}EPersona;


void initArray( EPersona lista[], int );
int obtenerEspacioLibre(EPersona lista[], int );
int buscarPorDni(EPersona lista[], int cantidadItems, int dni);
int getInt(int* input,char message[],char eMessage[], int lowLimit, int hiLimit);
int getName(char* input,char message[],char eMessage[], int lowLimit, int hiLimit);
EPersona cargarPersona(int, int, char nombre[]);
void mostrarUna(EPersona persona);
void mostrarPersonas(EPersona lista[], int cantidadItems);
void ordenarPorNombre(EPersona lista[], int cantidadItems);
void borrarPersona(EPersona lista[], int indice);
void pedirDatos(int* edad, int* dni,char*nombre);
void extraerDatosEdades(EPersona lista[], int edades[], int cantidadItems);
void crearGrafico(int edades[]);

#endif // FUNCIONES_H_INCLUDED
