#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peliculas.h"
#include "directores.h"
#include "ArrayList.h"
#include "input.h"
#define MAX_DIRECTOR 10


/** \brief Inicializa el array de directores adentro de la estructura ePelicula
 *
 * \param puntero int del array que se quiere inicializar
 * \param maxima longitud
 * \return devuelve [-1] si no pudo inicializar el array [0] si lo pudo inicializar
 *
 */
int initDirectoresPeliculas(int * auxDirector, int length)
{
    int i;
    int returnAux = -1;
    if(auxDirector != NULL && length> 0)
    {
        returnAux = 0;
        for(i=0;i<length;i++)
        {
            *(auxDirector+i) = -1;
        }
    }
    return returnAux;
}


/** \brief Solicita los datos al usuario de una pelicula
 *
 * \param pListPeliculas Arraylist* puntero al arraylist peliculas
 * \param pListDirectores Arraylist* puntero al arraylist directores
 * \param titulo char* puntero a char
 * \param anio int* puntero a int
 * \param nacionalidad int* puntero a int
 * \param director int* puntero a array
 * \param pedirId int si es [1] se solicita el id de la pelicula al usuario
 * \return [-1] si hay error [plistPelicula = NULL, pListDirectores = NULL, (!pListDirectores->isEmpty(pListDirectores),
           titulo=NULL, anio=NULL, nacionalidad=NULL, director=NULL, id= NULL)
           [0] si pudo obtener los datos
 *
 */
int datosPeliculas(ArrayList* pListPeliculas, ArrayList* pListDirectores ,char* titulo, int* anio, char* nacionalidad, int* director, int* id, int pedirId)
{
    int returnAux = -1;
    int auxInt;
    char auxTitulo[50];
    int auxAnio;
    char auxNacionalidad[30];
    int auxDirector[10];
    int auxId;
    int i, j;
    int cantidadDirectores;
    ePelicula* auxPelicula = NULL;
    eDirector* pDirector;
    if(pListPeliculas != NULL && pListDirectores !=NULL && (!pListDirectores->isEmpty(pListDirectores) && titulo !=NULL && anio != NULL && nacionalidad != NULL && director != NULL && id != NULL))
    {

        auxInt = initDirectoresPeliculas(auxDirector, MAX_DIRECTOR);
        if(auxInt != 0)
        {
            return returnAux;
        }
        do
        {
            auxInt = getStringSpace(auxTitulo, "Ingrese el titulo de la pelicula: ", "ERROR: maximo 50 caracteres", 0, 51);
        }while(auxInt!=0);
        strcpy(titulo, auxTitulo);

        do
        {
            auxInt = getInt(&auxAnio, "Ingrese el anio de la pelicula: ", "ERROR: minino 1890 maximo 2016\n", 1889, 2017);
        }while(auxInt!=0);
        *anio = auxAnio;
        do
        {
            auxInt = getString(auxNacionalidad, "Ingrese la nacionalidad de la pelicula: ", "ERROR: maximo 30 caracteres\n", 0, 31);
        }while(auxInt!=0);
        strcpy(nacionalidad, auxNacionalidad);
        if(pedirId)
        {
            do
            {
                auxInt = getInt(&auxId, "Ingrese el id: ", "ERROR: solamente numeros\n", 0, 1000);
                if(auxInt== 0)
                {
                    if(pListPeliculas->size > 0)
                    {
                        for(i= 0; i<pListPeliculas->size; i++)
                        {
                            auxPelicula = al_get(pListPeliculas, i);
                            if(auxPelicula->id == auxId)
                            {
                                auxInt = -1;
                                printf("Ya existe una pelicula  con ese ID!\n");
                                break;
                            }
                        }
                    }
                }

            }while(auxInt!=0);
            *id = auxId;
        }

        do
        {
            auxInt = getInt(&cantidadDirectores, "Ingrese la cantidad de directores que quiere tiene la pelicula: ", "ERROR: maximo 10\n",0, 11);
            if(auxInt == 0 && cantidadDirectores<= pListDirectores->size)
            {
                for(i = 0; i<cantidadDirectores; i++)
                {
                    do
                    {
                        auxInt = getInt(&auxDirector[i], "Ingrese el id del director: ", "solamente numeros\n", 0, 1000);
                        pDirector = getDirector(pListDirectores, auxDirector[i]);
                        if(pDirector == NULL )
                        {
                            printf("Ese director no esta cargado!\n");
                            auxInt = -1;
                        }
                        for(j=0;j<MAX_DIRECTOR;j++)
                        {
                            if(i != j)
                                if(auxDirector[i] == auxDirector[j])
                                {
                                    printf("Ya se ha cargado ese director en esta pelicula!\n");
                                    auxInt = -1;
                                    break;
                                }
                        }
                    }while(auxInt !=0);

                }

                    for(i= 0; i<10;i++)
                    {
                        *(director+i) = auxDirector[i];
                    }

            }
            else
            {
                printf("No hay tantos directores cargados!\n");
                auxInt = -1;
            }

        }while(auxInt!=0);



        returnAux = 0;

    }
    return returnAux;

}


/** \brief devuelve un puntero a ePelicula
 *
 * \param titulo char* puntero a char
 * \param anio char* puntero a char
 * \param nacionalidad char* puntero a char
 * \param director char* puntero a char
 * \param id char* puntero a id
 * \return [NULL] si pelicula =NULL, titulo= NULL, anio = NULL,nacionalidad = NULL, director = NULL, id = NULL
           [ePelicula] si se pudo obtener el elemento pelicula
 *
 */
ePelicula* nuevaPelicula(char* titulo, int* anio, char* nacionalidad, int* director, int* id)
{
    ePelicula* pelicula = malloc(sizeof(ePelicula));
    int i;
    if(pelicula !=NULL && titulo != NULL && anio != NULL && nacionalidad != NULL && director != NULL && id != NULL)
    {
        strcpy(pelicula->titulo, titulo);
        pelicula->anio = *anio;
        strcpy(pelicula->nacionalidad, nacionalidad);

        for( i = 0; i< MAX_DIRECTOR; i++)
        {
            pelicula->director[i] = director[i];
        }

        pelicula->id = *id;
    }
    return pelicula;
}


/** \brief agrega una pelicula al arrayList
 *
 * \param pListPeliculas ArrayList* puntero al arraylist de peliculas
 * \param pListDirectores ArrayList* puntero al arraylist de directores
 * \return [-1] si pListPeliculas = NULL, pListDirectores = NULL
 *         [0] si pudo agregar la pelicula
 */
int agregarPelicula(ArrayList* pListPeliculas, ArrayList* pListDirectores)
{
    int returnAux = -1;
    char titulo[50];
    int anio;
    char nacionalidad[30];
    int director[10];
    int id, index;
    ePelicula* pelicula;
    int auxInt;
    char respuesta;
    if(pListPeliculas != NULL && pListDirectores != NULL && (!pListDirectores->isEmpty(pListDirectores))  )
    {
        returnAux = 0;
        respuesta = mostrarMenu("1.Agregar pelicula\n2.Agregar pelicula en una posicion especifica\n", '1', '2');
        switch(respuesta)
        {
        case '1':
            auxInt = datosPeliculas(pListPeliculas, pListDirectores, titulo, &anio, nacionalidad,director, &id, 1);
            if(auxInt== 0)
            {
                pelicula = nuevaPelicula(titulo, &anio, nacionalidad, director, &id);
                if(pelicula != NULL)
                {
                    pListPeliculas->add(pListPeliculas, pelicula);
                }
            }
            break;
        case '2':
            if((!pListPeliculas->isEmpty(pListPeliculas)))
            {
                do
                {
                    auxInt = getInt(&index, "Ingrese el indice donde quiere guardar la pelicula: ", "error: numero no valido\n", -1, pListPeliculas->len(pListPeliculas));
                }while(auxInt!=0);

                auxInt = datosPeliculas(pListPeliculas, pListDirectores, titulo, &anio, nacionalidad, director, &id, 1);
                if(auxInt == 0)
                {
                    pelicula = nuevaPelicula(titulo, &anio, nacionalidad, director, &id);
                    if(pelicula != NULL)
                    {
                        pListPeliculas->push(pListPeliculas, index,pelicula);
                    }
                }
            }
            else
            {
                printf("No hay peliculas ingresadas!\n");
            }
                break;
        }
    }
    else if(pListDirectores->size <=0)
    {
        printf("No hay directores cargados\n");
    }
    return returnAux;

}


/** \brief imprime por pantalla la cantidad de peliculas que tenes
 *
 * \param pListPeliculas ArrayList* puntero al arraylist de peliculas
 * \param pListDirectores ArrayList* puntero al arraylist de directores
 * \return nada
 *
 */
void printArrayPeliculas(ArrayList* pListPelicula, ArrayList* pListDirector)
{
    ePelicula* pelicula;
    eDirector* director;
    int i,j, auxInt;
    int contadorDirectores = 0;
    //int indexDirector;
    if(pListDirector != NULL && pListPelicula != NULL && (!pListPelicula->isEmpty(pListPelicula)))
    {
        for(i=0;i<pListPelicula->size;i++)
        {
            pelicula = al_get(pListPelicula, i);
            printf("\nPelicula : %s \nNacionalidad: %s\nanio: %d\nid: %d\n", pelicula->titulo, pelicula->nacionalidad, pelicula->anio, pelicula->id);
            printf("Dirigida por:\n");

            for(j=0;j<MAX_DIRECTOR;j++)
            {
                if(pelicula->director[j] != -1)
                {
                    director = getDirector(pListDirector, pelicula->director[j]);
                    if(director != NULL)
                    {
                        printf("%s\n", director->nombre);
                        contadorDirectores++;
                    }
                }

            }
            if(contadorDirectores == 0)
            {
                printf("Director/es borrado/s\n");
            }
        }
        printf("-----Cantidad total de peliculas %d-----\n", auxInt = al_len(pListPelicula));
    }
    else if( pListPelicula->isEmpty(pListPelicula))
    {
        printf("No hay peliculas cargadas.\n");
    }
}


/** \brief buscar el indice de una pelicula segun el id pasado
 *
 * \param pListPeliculas ArrayList* puntero al arraylist de peliculas
 * \param id int de la pelicula que se quiere obtener
 * \return [-1] si pListPeliculas = NULL o id menor o igual a  0
 *
 */
int buscarIndexPelicula(ArrayList* pListPeliculas, int* id)
{
    int i;
    int index = -1;
    ePelicula* pPelicula;
    int auxId;
    int auxInt;



    if(pListPeliculas!=NULL)
    {
        do
        {
            auxInt = getInt(&auxId, "Ingrese id pelicula: ", "error: valido entre 1 y 1000",0, 1001);
        }while(auxInt!=0);

        for(i = 0; i<pListPeliculas->size; i++)
        {
            pPelicula = al_get(pListPeliculas, i);
            if(pPelicula->id == auxId)
            {
                index = i;
            }
            *id = auxId;
        }

    }
    return index;
}


/** \brief modifica los datos de una pelicula
 *
 * \param pListPeliculas ArrayList* puntero al arraylist de peliculas
 * \param pListDirectores ArrayList* puntero al arraylist de directores
 * \return [-1] si pListPeliculas = NULL, pListDirectores = NULL, pListPeliculas->isEmpty(pListPeliculas) = 1
 *         [0] si pudo modificar la pelicula
 */
int modificarPelicula(ArrayList* pListPeliculas, ArrayList* pListDirectores)
{
    int returnAux = -1;
    char titulo[50];
    int anio;
    char nacionalidad[30];
    int director[10];
    int index,id;
    ePelicula* pelicula;
    int auxInt;
    if(pListPeliculas != NULL && pListDirectores != NULL && (!pListPeliculas->isEmpty(pListPeliculas)))
    {
        returnAux = 0;
        index = buscarIndexPelicula(pListPeliculas, &id);
        if(index != -1)
        {
            auxInt = datosPeliculas(pListPeliculas, pListDirectores, titulo, &anio, nacionalidad,director, &id , 0);
            if(auxInt== 0)
            {
                pelicula = nuevaPelicula(titulo, &anio, nacionalidad, director, &id);
                pListPeliculas->set(pListPeliculas,index, pelicula);
            }
        }
        else
        {
            printf("no existe ninguna pelicula con ese id");
            returnAux = -1;
        }

    }
    else if(pListPeliculas->size <= 0)
    {
        printf("No se ha ingresado ninguna pelicula");
        returnAux = -1;

    }
    return returnAux;
}


/** \brief borra una pelicula o todas las peliculas
 *
 * \param pListPeliculas ArrayList* puntero al arraylist de peliculas
 * \return [NULL] si pListPeliculas = NULL, pListPeliculas->isEmpty(pListPeliculas), si el usuario elige no borrar las peliculas
 *
 */
ArrayList* borrarPelicula(ArrayList* pListPeliculas)
{
    int index, id;
    int auxInt;
    char opcion;
    ePelicula *pPelicula;
    ArrayList* backup;
    if(pListPeliculas != NULL && (!pListPeliculas->isEmpty(pListPeliculas)))
    {
        opcion = mostrarMenu("1.BORRAR PELICULA\n2.BORRAR PELICULAS\n", '1', '2');
        switch(opcion)
        {
            case '1':
                index = buscarIndexPelicula(pListPeliculas, &id);
                if(index != -1)
                {
                    backup = al_clone(pListPeliculas);
                    pPelicula = al_pop(pListPeliculas, index);
                    printf("Pelicula borrada:\n");
                    printf("Nombre: %s\nAnio: %d\nId: %d", pPelicula->titulo,pPelicula->anio,pPelicula->id);
                }
                else
                {
                    printf("No existe ninguna pelicula con ese id");
                }
                break;
            case '2':
                do
                {
                   auxInt = siOno(&opcion, "Desea borrar todas las peliculas? s/n\n", "ingrese 's' o 'n'", 's', 'n');
                }while(auxInt!=0);

                if(opcion == 's')
                {
                    backup = al_clone(pListPeliculas);
                    pListPeliculas->clear(pListPeliculas);
                }
                break;
        }
    }
    else if( pListPeliculas->isEmpty(pListPeliculas))
    {
        printf("No hay peliculas cargadas para borrar!");
    }

    return backup;
}


/** \brief compara 2 peliculas
 *
 * \param void* puntero a pPeliculaA
 * \param void* puntero a pPeliculaB
 * \return [1] si pPeliculaA es mayor que pPeliculaB
 *         [0] si son iguales
           [-1] si pPeliculaA es menor que pPeliculaB
 */
int compararPeliculas(void* pPeliculaA,void* pPeliculaB)
{
    int auxInt;
    ePelicula *aux, *aux1;
    if(pPeliculaA != NULL && pPeliculaB != NULL)
    {
        aux = (ePelicula*)pPeliculaA;
        aux1 = (ePelicula*) pPeliculaB;

        auxInt = strcmp(aux1->titulo, aux->titulo);

        if(auxInt == 0)
        {
            if(aux->anio > aux1->anio)
            {
                auxInt = 1;
            }
            else if(aux->anio < aux1->anio)
            {
                auxInt = -1;
            }
            else
            {
                auxInt = 0;
            }
        }
    }
    return auxInt;
}


/** \brief devuelva un puntero de tipo Arraylist con el ultimo elemento borrado del arraylist
 *
 * \param pList arrayList* puntero al ArrayList pList
 * \param pListRecupero arrayList* puntero al ArrayList pListRecupero
 * \return [NULL] si pList = NULL, pListRecupero = NULL, [arrayList*]
 *
 */
ArrayList* recuperarDatos(ArrayList* pList ,ArrayList* pListRecupero )
{
    int auxInt;
    ArrayList* returnAux;
    if(pList != NULL && pListRecupero != NULL)
    {
        auxInt = al_containsAll(pList, pListRecupero);
        if(auxInt != -1)
        {
            returnAux = al_clone(pListRecupero);
            if(pList != NULL)
            {
                pList->deleteArrayList(pList);
            }
        }
    }
    return returnAux;
}


/** \brief Muestra por pantalla las peliculas ordenadas y los directores cargados
 *
 * \param pListPeliculas ArrayList* puntero al arraylist de peliculas
 * \param pListDirectores ArrayList* puntero al arraylist de directores
 * \return [-1] si pListPeliculas = NULL, pListDirectores = NULL
 *
 */
int listar(ArrayList* pListPeliculas, ArrayList* pListDirectores)
{
    int returnAux = -1;
    char respuesta;
    ArrayList* auxPeliculas;
    if(pListPeliculas !=NULL && pListDirectores != NULL )
    {
        respuesta = mostrarMenu("1.Listar peliculas ordenadas\n2.Listar peliculas por orden de ingreso\n3.Listar Directores\n",'1','3');
        switch(respuesta)
        {
            returnAux = 0;
            case '1':
                auxPeliculas = al_clone(pListPeliculas);
                if(auxPeliculas != NULL)
                {
                    returnAux = 1;
                    auxPeliculas->sort(auxPeliculas, compararPeliculas, 1);
                    printArrayPeliculas(auxPeliculas, pListDirectores);
                    auxPeliculas->deleteArrayList(auxPeliculas);
                }
                break;
            case '2':
                printArrayPeliculas(pListPeliculas, pListDirectores);
                break;
            case '3':
                returnAux = 1;
                printArrayDirectores(pListDirectores);
                break;
        }

    }
    return returnAux;
}


/** \brief Devuelve la cantidad de directores que tiene el elemento pasado por paramentro
 *
 * \param void* pPeliculaA puntero a void
 * \return devuelve la cantidad de directores que posee una pelicula
 *
 */
int cantidadDirectores(void* pPeliculaA)
{
    int cantidad = 0;
    int i;
    ePelicula *aux;
    if(pPeliculaA != NULL)
    {
        aux = (ePelicula*) pPeliculaA;
        for(i=0;i<10; i++)
        {
            if(aux->director[i] != -1)
            {
                cantidad++;
            }
        }
    }
    return cantidad;
}


/** \brief compara la cantidad de directores de 2 peliculas
 *
 * \param void* pPeliculaA puntero a void
 * \param void* pPeliculaB puntero a void
 * \return [1] si pPeliculaA tiene mas directores
 *         [0] si tienen la misma cantidad de directores
 *         [-1] si pPeliculaB tiene mas directores
 */
int comparePeliculaMasDirectores(void* pPeliculaA, void* pPeliculaB)
{
    int returnAux;
    int cantidadA, cantidadB;
    ePelicula *aux, *aux1;
    if(pPeliculaA !=NULL && pPeliculaB != NULL)
    {
        aux = (ePelicula*) pPeliculaA;
        aux1 = (ePelicula*) pPeliculaB;
        cantidadA = cantidadDirectores(aux);
        cantidadB = cantidadDirectores(aux1);
        if( cantidadA > cantidadB)
        {
            returnAux = 1;
        }
        else if(cantidadA < cantidadB)
        {
            returnAux = -1;
        }
        else
        {
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief devuelve un Arraylist con las 5 peliculas con mas directores
 *
 * \param ArrayList* pListPeliculas puntero al Arraylist
 * \return [NULL] si el paramentro es NULL o un puntero a arraylist si esta ok
 *
 */
ArrayList* peliculasMasDirectores(ArrayList* pListPeliculas)
{
    ArrayList* auxPeliculas;
    if(pListPeliculas != NULL)
    {
        auxPeliculas = al_clone(pListPeliculas);
        auxPeliculas->sort(auxPeliculas, comparePeliculaMasDirectores, 1);
        if(auxPeliculas->len(auxPeliculas) > 5)
        {
            auxPeliculas = al_subList(auxPeliculas, 0,5);
        }
    }
    return auxPeliculas;

}

/** \brief segun lo que elija el usuario, imprime un listado con el top 5 de peliculas o te dice
           una pelicula esta en ese top 5
 *
 * \param ArrayList* pListPeliculas puntero al arraylist pListPeliculas
 * \param ArrayList* pListDirectores puntero al arraylist pListDirectores
 * \return [-1] si pListPeliculas es NULL o pListDirectores es NULL
           [0] si no pudo devolver el top 5 o la pelicula
           [1] si pudo realizar lo pedido
 *
 */
int informar(ArrayList* pListPeliculas, ArrayList* pListDirectores)
{
    int returnAux = -1;
    int auxInt;
    int id;
    char respuesta;

    ArrayList* auxPeliculas;
    int index;
    ePelicula* auxPelicula;
    if(pListPeliculas != NULL && pListDirectores != NULL && (!pListPeliculas->isEmpty(pListPeliculas)) && (!pListDirectores->isEmpty(pListDirectores)))
    {
        returnAux = 0;
        respuesta = mostrarMenu("1.Top 5 peliculas con mas directores\n2.Buscar pelicula en top 5ç\n", '1', '2');
        switch(respuesta)
        {
            case '1':
                auxPeliculas = peliculasMasDirectores(pListPeliculas);
                if(auxPeliculas!=NULL)
                {
                    printArrayPeliculas(auxPeliculas, pListDirectores);
                }
                break;
            case '2':
                auxPeliculas = peliculasMasDirectores(pListPeliculas);
                if(auxPeliculas!= NULL)
                {
                    index = buscarIndexPelicula(pListPeliculas, &id);
                    if(index != -1)
                    {
                        auxPelicula = al_get(pListPeliculas, index);
                        if(auxPelicula != NULL)
                        {
                            auxInt = al_contains(auxPeliculas, auxPelicula);
                            if(auxInt == 1)
                            {
                                printf("La pelicula se encuentra en el top 3\n");
                            }
                            else if( auxInt == 0)
                            {
                                printf("La pelicula no se encuentra en el top 3\n");
                            }
                        }
                    }
                }
                break;
        }
    }
    return returnAux;
}


/** \brief Guarda los elementos del arrayList
 *
 * \param pList arraylist* puntero al arraylist
 * \param nombreArchivo char* puntero a char
 * \param opcion int opcion del menu
 * \return
 *
 */
int guardarDatos(ArrayList* pList, char* nombreArchivo, int opcion)
{
    FILE* pArch;
    ePelicula* auxPelicula;
    eDirector* auxDirector;
    int i;
    int returnAux = -1;
    if(pList != NULL && nombreArchivo!= NULL && (opcion == 1 || opcion == 2) )
    {
        returnAux = 0;
        pArch = fopen(nombreArchivo, "wb");
        if( pArch != NULL)
        {
            switch(opcion)
            {
                case 1:
                    for(i = 0; i< pList->len(pList); i++)
                    {
                        auxPelicula = al_get(pList, i);
                        if(auxPelicula != NULL)
                        {
                            fwrite(auxPelicula, sizeof(ePelicula),1, pArch);
                        }
                        else if( auxPelicula == NULL)
                        {
                            returnAux = -1;
                            break;
                        }
                    }

                    break;
                case 2:
                    for(i = 0; i< pList->len(pList); i++)
                    {
                        auxDirector = al_get(pList, i);
                        if(auxDirector != NULL)
                        {
                            fwrite(auxDirector, sizeof(eDirector), 1, pArch);
                        }
                        else if( auxDirector == NULL)
                        {
                            returnAux = -1;
                            break;
                        }
                    }
                    break;
            }
            fclose(pArch);
        }
        else
        {
            returnAux = -1;
        }
    }
    return returnAux;
}


/** \brief carga los datos previamente guardados.
 *
 * \param pList arraylist* puntero al arraylist
 * \param nombreArchivo char* puntero a char
 * \param opcion int opcion del menu
 * \return [-1] si pList = NULL, nombreArchivo = NULL
           [0] si pudo cargar los datos
 *
 */
int cargarDatos(ArrayList* pList, char* nombreArchivo, int opcion )
{
    FILE* pArch;
    ePelicula* auxPelicula;
    eDirector* auxDirector;
    int auxInt;
    int flag = 1;
    int returnAux = -1;

    if(pList != NULL && nombreArchivo != NULL)
    {
        returnAux = 0;
        pArch = fopen(nombreArchivo, "rb");
        if(pArch == NULL)
        {

            pArch = fopen(nombreArchivo, "wb");
            if(pArch == NULL)
            {
                printf("ERROR");
            }
            flag = 0;
        }
        if(flag == 1)
        {
            switch(opcion)
            {
                case 1:
                    while(!feof(pArch))
                    {
                        auxPelicula = malloc(sizeof(ePelicula));
                        auxInt = fread(auxPelicula, sizeof(ePelicula),1,pArch);
                        if(auxInt != 1)
                        {
                            if(feof(pArch))
                            {
                                break;
                            }
                            else
                            {
                                printf("error de lectura\n");
                            }
                        }
                        pList->add(pList, auxPelicula);
                    }
                    break;
                case 2:
                    while(!feof(pArch))
                    {
                        auxDirector = malloc(sizeof(eDirector));
                        auxInt = fread(auxDirector, sizeof(eDirector),1,pArch);
                        if(auxInt != 1)
                        {
                            if(feof(pArch))
                            {
                                break;
                            }
                            else
                            {
                                printf("error de lectura\n");
                            }
                        }
                        pList->add(pList, auxDirector);
                    }
                    break;
            }
        }
        fclose(pArch);
    }
    return returnAux;
}


