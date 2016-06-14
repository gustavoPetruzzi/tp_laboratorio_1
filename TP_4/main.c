#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "peliculas.h"
#include "directores.h"
#include "input.h"
#define CLEAR system("cls")
#define PAUSE system("pause")

int main()
{
    ArrayList* listPeliculas, *listDirectores,*auxPeliculas, *auxDirectores;
    ArrayList *backupDirectores = NULL;
    ArrayList *backupPeliculas = NULL;
    int auxInt;
    char opcion;
    listPeliculas = al_newArrayList();
    listDirectores = al_newArrayList();

    //readMockDirector(listDirectores);
    cargarDatos(listPeliculas, "peliculas.dat", 1);
    cargarDatos(listDirectores, "directores.dat", 2);

    //readPelicula(listPeliculas);
    if(listPeliculas != NULL && listDirectores != NULL)
    {
        do
        {
            opcion = mostrarMenu("1.ALTAS PELICULAS\n2.MODIFICAR PELICULA\n3.BAJA PELICULA\n4.NUEVO DIRECTOR\n5.ELIMINAR DIRECTOR\n6.RECUPERAR\n7.INFORMAR\n8.LISTAR\n9.SALIR\n", '1', '9');

            switch(opcion)
            {
                case '1':
                    auxInt = agregarPelicula(listPeliculas, listDirectores);
                    if(auxInt == 0)
                    {
                        printf("Pelicula agregada\n");
                    }
                    PAUSE;
                    CLEAR;
                    break;
                case '2':
                    auxInt = modificarPelicula(listPeliculas, listDirectores);
                    if(auxInt == 0)
                    {
                        printf("Pelicula modificada");
                    }
                    PAUSE;
                    CLEAR;
                    break;
                case '3':
                    backupPeliculas = borrarPelicula(listPeliculas);

                    PAUSE;
                    CLEAR;
                    break;
                case '4':
                    auxInt = agregarDirector(listDirectores);
                    if(auxInt == 0)
                    {
                        printf("Director cargado!");
                    }
                    PAUSE;
                    CLEAR;
                    break;
                case '5':
                    backupDirectores = borrarDirector(listDirectores);
                    if(backupDirectores != NULL)
                    {
                        printf("Director borrado");
                    }
                    PAUSE;
                    CLEAR;
                    break;
                case '6':
                    opcion = mostrarMenu("1.RECUPERAR PELICULAS\n2.RECUPERAR DIRECTORES\n", '1', '2');
                    switch(opcion)
                    {
                    case '1':
                        auxPeliculas = recuperarDatos(listPeliculas, backupPeliculas);
                        if(auxPeliculas == NULL)
                        {
                            printf("No se ha podido recuperar peliculas!\n");
                        }
                        else
                        {
                            printf("Peliculas recuperadas\n");
                            listPeliculas = al_clone(auxPeliculas);
                            auxPeliculas->deleteArrayList(auxPeliculas);
                        }
                        break;
                    case '2':

                        auxDirectores = recuperarDatos(listDirectores, backupDirectores);
                        if(auxDirectores == NULL)
                        {
                            printf("No se ha podido recuperar los directores\n");
                        }
                        else
                        {
                            printf("Directores recuperados\n");
                            listDirectores = al_clone(auxDirectores);
                            auxDirectores->deleteArrayList(auxDirectores);
                        }
                        break;
                    }
                    PAUSE;
                    CLEAR;
                    break;
                case '7':
                    auxInt =informar(listPeliculas, listDirectores);
                    if(auxInt == -1)
                    {
                        printf("No se ha podido informar");
                    }
                    PAUSE;
                    CLEAR;
                    break;
                case '8':
                    auxInt = listar(listPeliculas, listDirectores);
                    PAUSE;
                    CLEAR;
                    break;
                case '9':

                    auxInt = guardarDatos(listPeliculas, "peliculas.dat", 1);
                    if(auxInt != 0)
                        printf("Hubo un error al guardar las peliculas");

                    auxInt = guardarDatos(listDirectores, "directores.dat", 2);
                    if(auxInt != 0)
                        printf("Hubo un error al guardar los directores");

                    listDirectores->deleteArrayList(listDirectores);
                    listPeliculas->deleteArrayList(listPeliculas);
                    break;
                default:
                    break;
            }
        }while(opcion!='9');
    }
    return 0;
}
void readMockDirector(ArrayList* pList)
{
    FILE* pArch;
    eDirector* pDirector;
    char nombre[50];
    char fecha[30];
    char paisOrigen[50];
    char auxIdDirector;

    pArch = fopen("MOCK_DATA.txt", "r");

    while(!(feof(pArch)))
    {
        pDirector = malloc(sizeof(eDirector));
        fscanf(pArch,"%[^,],%[^,],%[^,],%s\n", nombre, fecha, paisOrigen, &auxIdDirector);
        strcpy(pDirector->nombre, nombre);
        strcpy(pDirector->fechaNacimiento, fecha);
        strcpy(pDirector->paisOrigen, paisOrigen);
        pDirector->idDirector =atoi(&auxIdDirector);
        pList->add(pList, pDirector);
    }
    fclose(pArch);
}
