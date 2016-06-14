#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directores.h"
#include "input.h"
#include "ArrayList.h"


/** \brief Solicita los datos al usuario de una pelicula
 *
 * \param pListDirectores ArrayList* puntero al arraylist directores
 * \param nombre char* puntero a array de char
 * \param fechaNacimiento char* puntero a array de char
 * \param paisOrigen char* puntero a array de char
 * \param idDirector int* puntero a int

 * \return [-1] si pListDirectores = NULL, nombre = NULL, fechaNacimiento = NULL,  paisOrigen = NULL, idDirector = NULL
           [0] si obtuvo los datos
 *
 */
int datosDirectores(ArrayList* pListDirectores,char* nombre, char* fechaNacimiento,char* paisOrigen,int* idDirector)
{
    int auxInt, i;
    char auxNombre[50];
    char auxFechaNacimiento[11];
    char auxPaisOrigen[50];
    int auxIdDirector;
    int returnAux = -1;
    eDirector* pDirector;

    if(pListDirectores != NULL && nombre != NULL && fechaNacimiento != NULL && paisOrigen != NULL && idDirector != NULL)
    {
        returnAux = 0;
        do
        {
            auxInt = getInt(&auxIdDirector, "Ingrese el id del director: ", "error: id invalido", 0, 501);
            for(i = 0; i<pListDirectores->size; i++)
            {
                pDirector = al_get(pListDirectores, i);
                if(pDirector->idDirector == auxIdDirector)
                {
                    printf("Ya existe alguien con ese id!");
                    auxInt = -1;
                    break;
                }
            }
        }while(auxInt!= 0);
        *idDirector = auxIdDirector;
        do
        {
            auxInt = getName(auxNombre, "Ingrese el nombre del director: ", "error: maximo 50 caracteres", 0, 51);
            for(i=0;i<pListDirectores->size;i++)
            {
                pDirector = al_get(pListDirectores, i);
                if(strcmp(pDirector->nombre, auxNombre)== 0)
                {
                    printf("Ya existe alguien con ese nombre!");
                    auxInt = -1;
                    break;
                }
            }
        }while(auxInt!=0);
        strcpy(nombre, auxNombre);

        do
        {
            auxInt =getString(auxFechaNacimiento, "Ingrese la fecha de nacimiento: ", "error: ingrese fecha en formato dd/mm/aaaa", 0, 12);
        }while(auxInt!=0);
        strcpy(fechaNacimiento, auxFechaNacimiento);
        do
        {
            auxInt = getString(auxPaisOrigen, "Ingrese el pais de origen del director: ", "error: maximo 50 caracteres", 0, 51);
        }while(auxInt!=0);
        strcpy(paisOrigen, auxPaisOrigen);
    }
    return returnAux;
}


/** \brief Devuelve un puntero a eDirector
 *
 * \param nombre char* puntero a array de char
 * \param fechaNacimiento char* puntero a array de char
 * \param paisOrigen char* puntero a array de char
 * \param idDirector int* puntero a int
 * \return [NULL] si nombre = NULL, fechaNacimiento = NULL, paisOrigen = NULL, idDirector = NULL
 *         [puntero a eDirector] si esta todo ok
 */
eDirector* nuevoDirector(char* nombre, char* fechaNacimiento, char* paisOrigen, int* idDirector)
{
    eDirector* pDirector = malloc(sizeof(eDirector));
    if(nombre != NULL && fechaNacimiento != NULL && paisOrigen != NULL && idDirector != NULL && pDirector != NULL)
    {

        strcpy(pDirector->nombre, nombre);
        strcpy(pDirector->fechaNacimiento, fechaNacimiento);
        strcpy(pDirector->paisOrigen, paisOrigen);
        (pDirector->idDirector) = *idDirector;
    }
    return pDirector;
}


/** \brief Agrega un elemento de tipo eDirector al arraylist
 *
 * \param pListDirectores ArrayList* puntero al arraylist directores
 * \return [-1] si pListDirectores = NULL
           [0] si pudo agregar el elemento
 *
 */
int agregarDirector(ArrayList* pListDirectores)
{
    int returnAux = -1;
    char auxNombre[50];
    char auxFechaNacimiento[12];
    char auxPaisOrigen[50];
    int auxIdDirector;
    int auxInt;
    eDirector* pDirector;
    if(pListDirectores != NULL)
    {
        returnAux = 0;
        auxInt = datosDirectores(pListDirectores, auxNombre, auxFechaNacimiento, auxPaisOrigen, &auxIdDirector);
        if(auxInt == 0)
        {
            pDirector = nuevoDirector(auxNombre, auxFechaNacimiento, auxPaisOrigen, &auxIdDirector);
            if(pDirector != NULL)
            {
                pListDirectores->add(pListDirectores, pDirector);
            }
        }
    }
    return returnAux;
}


/** \brief imprime por pantalla el array de directores
 *
 * \param pListDirectores ArrayList* puntero al arraylist directores
 * \return -
 *
 */
void printArrayDirectores(ArrayList* pListDirectores)
{
    eDirector* pDirector;
    int i;
    if(pListDirectores != NULL && (!pListDirectores->isEmpty(pListDirectores)))
    printf("-----Cantidad total de directores: %d-----", pListDirectores->len(pListDirectores));
    for(i=0;i<pListDirectores->size;i++)
    {
        pDirector = al_get(pListDirectores, i);

        printf("\n");
        printf("%s %s %s %d\n", pDirector->nombre, pDirector->paisOrigen, pDirector->fechaNacimiento, pDirector->idDirector);


    }
}


/** \brief Devuelve un puntero de eDirector
 *
 * \param pListDirectores ArrayList* puntero al arraylist directores
 * \param int idDirector
 * \return [NULL] si pListDirector = NULL, idDirector <= 0, o no existe un director con idDirector
           un puntero de eDirector si esta ok
 */
eDirector* getDirector(ArrayList* pListDirector, int idDirector)
{
    eDirector* auxDirector = NULL;
    int i;
    int flagIsEmpty = 1;
    if(pListDirector != NULL && idDirector > 0)
    {
        for(i=0;i<pListDirector->size;i++)
        {
            auxDirector = al_get(pListDirector, i);
            if(auxDirector->idDirector == idDirector)
            {
                flagIsEmpty = 0;
                break;
            }
        }
        if(flagIsEmpty == 1)
        {
            auxDirector = NULL;
        }
    }
    return auxDirector;
}


/** \brief Elimina un elemento de tipo eDirector del arraylist
 *
 * \param pListDirectores ArrayList* puntero al arraylist directores
 * \return [NULL] si pListDirectores = NULL, pListDirectores->isEmpty(pListDirectores) y respuesta es 'n'
 *          un puntero al arraylist si pudo borrar el elemento
 */
ArrayList* borrarDirector(ArrayList* pListDirectores)
{
    int returnAux = -1;
    int auxInt, i;
    char auxNombre[50];
    eDirector* pDirector;
    ArrayList* backup;
    char respuesta;
    if(pListDirectores != NULL && (!pListDirectores->isEmpty(pListDirectores)))
    {
        do
        {
            auxInt = getName(auxNombre, "Ingrese el nombre del director a eliminar:", "ERROR: maximo 51 caracteres", 0, 51);
        }while(auxInt!=0);
        for(i=0;i<pListDirectores->size;i++)
        {
            pDirector = al_get(pListDirectores, i);
            if(strcmp(pDirector->nombre, auxNombre) == 0)
            {
                returnAux = 0;
                printf("nombre: %s\nid: %d\nFecha de nacimiento %s\nPais de origen: %s", pDirector->nombre, pDirector->idDirector, pDirector->fechaNacimiento, pDirector->paisOrigen);
                do
                {
                    auxInt = siOno(&respuesta, "Desea eliminarlo? s/n", "ERROR: ingrese 's' o 'n'", 's', 'n');
                }while(auxInt!=0);
                if(respuesta == 's')
                {
                    backup = al_clone(pListDirectores);
                    pListDirectores->remove(pListDirectores, i);
                }
                break;
            }

        }
        if(returnAux != 0)
        {
            printf("No existe ningun director con ese nombre!");
        }
    }
    return backup;
}


