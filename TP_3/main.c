#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define QTY 50
#define CLEAR system("cls")
#define PAUSE system("pause")
int main()
{
    char seguir='s';
    int opcion=0;
    int auxInt;
    EMovie peliculas[QTY];

    auxInt = cargarArchivo(peliculas, QTY);

    if(auxInt == 0)
    {
        while(seguir=='s')
        {
            printf("1- Agregar pelicula\n");
            printf("2- Borrar pelicula\n");
            printf("3- Modificar pelicula\n");
            printf("4- Generar pagina web\n");
            printf("5- Salir\n");

            scanf("%d",&opcion);
            CLEAR;
            switch(opcion)
            {
                case 1:
                    auxInt = agregarPelicula(peliculas, QTY);
                    if(auxInt == 0)
                    {
                        printf("Pelicula cargada\n");
                    }
                    else
                    {
                        printf("No se ha podido cargar la pelicula");
                    }
                    PAUSE;
                    CLEAR;
                    break;
                case 2:
                    auxInt = borrarPelicula(peliculas, QTY);
                    if(auxInt !=0)
                    {
                        printf("Error\n");
                    }
                    PAUSE;
                    CLEAR;
                    break;
                case 3:
                    auxInt = modificarPelicula(peliculas, QTY);
                    if(auxInt !=0)
                    {
                        printf("Error\n");
                    }
                    PAUSE;
                    CLEAR;
                   break;
                case 4:
                    generarPagina(peliculas, QTY);
                    break;
                case 5:
                    auxInt = guardarEnArchivo(peliculas, QTY);
                    if(auxInt == 0)
                    {
                        printf("Archivo guardado");
                    }
                    seguir = 'n';
                    break;
            }
        }
    }

    return 0;
}
