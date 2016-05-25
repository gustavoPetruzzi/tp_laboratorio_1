#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

/** \brief inicializa el array de estructuras
 *
 * \param EMovie* pMovie puntero al array a inicializar
 * \param int length tamaño maximo del array
 * \return devuelve [0] si lo pudo inicializar, [-1] si no
 *
 */
int initArrayEstructuras(EMovie* pMovie, int length)
{
    int i;
    int retorno = -1;
    if(pMovie != NULL && length> 0)
    {
        retorno = 0;
        for(i=0; i<length; i++)
        {
            (pMovie+i)->isEmpty = 1;
        }
    }
    return retorno;
}



/** \brief Carga el archivo un archivo binario y si no existe, lo crea
 *
 * \param EMovie* pMovie puntero donde guarda los archivos despues de cargarlos
 * \param int length tamaño maximo del array
 * \return [0] si lo pudo cargar, [1] si no pudo
 *
 */

int cargarArchivo(EMovie *pMovie, int length)
{
	int flag = 0;
	FILE *pArch;
	int auxInt;

	if(pMovie != NULL && length>0)
    {
        pArch=fopen("binMovie.dat", "rb");
        if(pArch==NULL)
        {
            pArch= fopen("binMovie.dat", "wb");

            flag = initArrayEstructuras(pMovie, length);

            if(flag == -1)
            {
                return 1;
            }
            if(pArch==NULL)
            {
                return 1;
            }
        }
        if(flag ==0)
        {
            while(!feof(pArch))
            {
                auxInt =fread(pMovie,sizeof(EMovie),length,pArch);
                if(auxInt!=length)
                {
                    if(feof(pArch))
                    {
                        break;
                    }
                    else
                    {
                        printf("No se leyo el ultimo registro");
                    }
                }
            }
        }
    }
	fclose(pArch);
	return 0;
}




/** \brief Guarda la estructura y sus datos en un archivo binario previamente cargado
 *
 * \param EMovie* pMovie puntero al array de estructura
 * \param int length tamaño maximo del array
 * \return [0] si pudo guardar el archivo [1] si no pudo
 *
 */

int guardarEnArchivo(EMovie * pMovie, int length)
{
    char opcion;
    FILE *pArch;
    int auxInt;
    if(pMovie != NULL && length> 0)
    {
        do
        {
            auxInt = siOno(&opcion, "Desea guardar? s/n ","Error: Ingrese 's' o 'n'", 's', 'n');
        }while(auxInt!=0);
        if(auxInt == 0 && opcion =='s')
        {
            pArch=fopen("binMovie.dat","wb");
            if(pArch == NULL)
            {
                printf("Un error ha ocurrido");
                return 1;
            }
            fwrite(pMovie,sizeof(EMovie),length,pArch);
        }
        else
        {
            printf("archivo no guardado");
            return  1;
        }
        fclose(pArch);
    }

	return 0;
}



/** \brief Busca un espacio libre en el array
 *
 * \param EMovie* pMovie puntero al array donde busca el espacio libre
 * \param int length tamaño maximo del array
 * \return el espacio libre si existe, [-1] si no hay espacio
 *
 */
int buscarLibre(EMovie* pMovie, int length)
{
    int i;
    int indice = -1;
    if(pMovie != NULL && length> 0)
    {
        for(i = 0; i<length; i++)
        {
            if( (pMovie+i)->isEmpty == 1 )
            {
                indice = i;
                break;
            }
        }
    }
    return indice;
}


/** \brief Busca el lugar en el array donde esta el nombre
 *
 * \param EMovie* pMovie puntero al array donde busca el espacio libre
 * \param int length tamaño maximo del array
 * \return [-1] si no pudo encontrar el nombre, si lo encontro devuelve el indice
 *
 */

int buscarPorNombre(EMovie* pMovie, int length)
{
    int i;
    int indice = -1;
    char auxTitulo[50];
    int auxInt;
    if(pMovie != NULL && length> 0)
    {
        do
        {
            auxInt = getStringSpace(auxTitulo, "Ingrese el titulo de la pelicula: ", "Error: Maximo 50 caracteres\n", 0, 21);
        }while(auxInt!=0);

        for(i = 0; i<length; i++)
        {
            if((pMovie+i)->isEmpty == 0)
            {
                if(strcmp((pMovie+i)->titulo, auxTitulo) == 0)
                {
                    indice = i;
                    break;
                }
            }
        }
    }
    return indice;
}



/** \brief pide los datos al usuarios de un elemento del array de la estructura
 *
 * \param EMovie* pMovie puntero al array
 * \param int length tamaño maximo del array
 * \param char* titulo puntero al dato pedido al usuario
 * \param char* genero puntero al dato pedido al usuario
 * \param int* duracion puntero al dato pedido al usuario
 * \param char* descripcion puntero al dato pedido al usuario
 * \param int* puntaje puntero al dato pedido al usuario
 * \param char* linkImagen puntero al dato pedido al usuario
 * \param int primera vez se pone [1] si se ingresa por primera vez o [0] para modificar
 * \return [-1] si no pudo pedir los datos o [0] si pudo pedir los datos
 *
 */

int pedirDatos(EMovie* pMovie, int length, char* titulo, char* genero, int* duracion, char* descripcion, int* puntaje, char* linkImagen, int primeraVez)
{
    char auxTitulo[50];
    char auxGenero[20];
    int auxDuracion;
    char auxDescripcion[100];
    int auxPuntaje;
    char auxLinkImagen[100];
    int auxInt;
    int retorno = -1;
    int i;

    if( pMovie != NULL && length> 0 && titulo != NULL && genero != NULL && duracion != NULL && descripcion != NULL && puntaje != NULL && linkImagen != NULL)
    {
        retorno = 0;

        do
        {
            auxInt = getStringSpace(auxTitulo, "Ingrese el titulo de la pelicula: ", "Error: Maximo 50 caracteres", 0, 51);
            if(primeraVez == 1)
            {
                for(i=0;i<length; i++)
                {
                    if(strcmp((pMovie+i)->titulo, auxTitulo) == 0)
                    {
                        auxInt = -1;
                        printf("Ya existe una pelicula con ese titulo!\n");
                        break;
                    }
                }
            }
        }while(auxInt!=0);
        strcpy(titulo, auxTitulo);

        do
        {
            auxInt = getStringSpace(auxGenero, "Ingrese el genero: ", "Error: Maximo 20 caracteres\n", 0, 21);
        }while(auxInt!=0);
        strcpy(genero, auxGenero);

        do
        {
            auxInt = getStringSpace(auxDescripcion, "Ingrese la descripcion: ", "Error: Maximo 100 caracteres\n", 0, 101);
        }while(auxInt!=0);
        strcpy(descripcion, auxDescripcion);

        do
        {
            auxInt = getString(auxLinkImagen, "Ingrese el link de la imagen: ", "Error: Maximo 100 caracteres\n", 0, 101);
        }while(auxInt!=0);
        strcpy(linkImagen, auxLinkImagen);

        do
        {
            auxInt = getInt(&auxDuracion, "Ingrese la duracion de la pelicula de la imagen: ", "Error: duracion minima 60 minutos\n", 59, 961);
            // VALIDO HASTA 961 MINUTOS PORQUE LA PELICULA MAS LARGA HASTA EL MOMENTO ES DE 15HS
        }while(auxInt!=0);
        *duracion = auxDuracion;

        do
        {
            auxInt = getInt(&auxPuntaje, "Ingrese el puntaje: ", "Error: puntaje valido del 1 al 10\n", 0, 11);
        }while(auxInt!=0);
        *puntaje = auxPuntaje;
    }
    return retorno;
}


/** \brief carga los datos pasados por parametro a una variable de tipo EMovie
 *
 * \param char* titulo puntero al dato pedido al usuario
 * \param char* genero puntero al dato pedido al usuario
 * \param int* duracion puntero al dato pedido al usuario
 * \param char* descripcion puntero al dato pedido al usuario
 * \param int* puntaje puntero al dato pedido al usuario
 * \param char* linkImagen puntero al dato pedido al usuario
 * \return una variable de tipo Emovie
 *
 */

EMovie cargarDatos(char* titulo, char* genero, int* duracion, char* descripcion, int* puntaje, char* linkImagen)
{
    EMovie auxPelicula;
    if(titulo != NULL && genero !=NULL && duracion !=NULL && descripcion !=NULL && puntaje != NULL && linkImagen != NULL)
    {
        strcpy(auxPelicula.titulo, titulo);
        strcpy(auxPelicula.genero, genero);
        auxPelicula.duracion = *duracion;
        strcpy(auxPelicula.descripcion, descripcion);
        auxPelicula.puntaje = *puntaje;
        strcpy(auxPelicula.linkImagen, linkImagen);
        auxPelicula.isEmpty = 0;
    }
    return auxPelicula;
}



/** \brief agrega un elemento al array de estructuras
 *
 * \param EMovie* pMovie puntero al array
 * \param int length tamaño maximo del array
 * \return [-1] si no pudo agregar el elemento, [0] si lo pudo agregar
 *
 */

int agregarPelicula(EMovie *pMovie, int length)
{
    int retorno = -1;
    int indice;

    char titulo[50];
    char genero[20];
    int duracion;
    char descripcion[100];
    int puntaje;
    char linkImagen[100];
    int auxInt;
    if(pMovie != NULL && length > 0)
    {
        retorno = 0;
        indice = buscarLibre(pMovie, length);
        if(indice !=-1)
        {
            auxInt = pedirDatos(pMovie, length, titulo, genero, &duracion, descripcion, &puntaje, linkImagen, 1);
            if(auxInt == 0)
            {
                *(pMovie+indice) = cargarDatos(titulo, genero, &duracion, descripcion, &puntaje, linkImagen);
            }
            else
            {
                printf("No se ha podido cargar la pelicula\n");
            }
        }
        else
        {
            printf("No hay mas lugar para cargar peliculas\n");
        }
    }
    return retorno;
}




/** \brief Borra un elemento del array de estructuras
 *
 * \param EMovie* pMovie puntero al array
 * \param int length tamaño maximo del array
 * \return [-1] si no pudo borrar la pelicula, [0] si pudo borrarla
 *
 */
int borrarPelicula(EMovie* pMovie, int length)
{
    char auxChar;
    int indice;
    int auxInt;
    int retorno = -1;
    if(pMovie != NULL && length>0)
    {
        retorno = 0;
        indice = buscarPorNombre(pMovie, length);
        if(indice != -1)
        {
            do
            {
                auxInt = siOno(&auxChar, "Desea borrar? s/n", "error: Ingrese 's' para borrar o 'n' para cancelar\n", 's', 'n');
            }while(auxInt !=0);
            if(auxChar == 's')
            {
                (pMovie+indice)->isEmpty = 1;
                printf("Pelicula borrada\n");
            }
            else
            {
                printf("Accion cancelada\n");
            }
        }
        else
        {
            printf("No existe ninguna pelicula con ese nombre\n");
        }
    }
    return retorno;
}


/** \brief modifica un elemento del array
 *
 * \param EMovie* pMovie puntero al array
 * \param int length tamaño maximo del array
 * \return [-1] si no pudo borrar la pelicula, [0] si pudo borrarla
 *
 */
int modificarPelicula(EMovie* pMovie, int length)
{
    int retorno = -1;
    int indice;
    char titulo[50];
    char genero[20];
    int duracion;
    char descripcion[100];
    int puntaje;
    char linkImagen[100];
    int auxInt;
    char auxChar;

    if(pMovie !=NULL && length> 0)
    {
        retorno = 0;
        indice = buscarPorNombre(pMovie, length);
        if(indice != -1)
        {
            do
            {
                auxInt = siOno(&auxChar, "Desea modificar? s/n", "error: Ingrese 's' para borrar o 'n' para cancelar\n", 's', 'n');
            }while(auxInt !=0);
            if(auxChar == 's')
            {
                auxInt = pedirDatos(pMovie, length, titulo, genero, &duracion, descripcion, &puntaje, linkImagen, 0);
                if(auxInt == 0)
                {
                    *(pMovie+indice) = cargarDatos(titulo, genero, &duracion, descripcion, &puntaje, linkImagen);
                    printf("Pelicula modificada\n");
                }
            }
            else
            {
                printf("Accion cancelada\n");
            }
        }
        else
        {
            printf("No existe ninguna pelicula con ese nombre");
        }
    }
    return retorno;
}

/** \brief guarda un archivo de texto pasado por parametro
 *
 * \param FILE pFile archivo que se guarda
 * \return devuelve un puntero al archivo guardado por parametro
 *
 */
char * leerArchivo(FILE* pFile)
{
    int cantidad;
    int auxInt;
    char * pArchivo;

    if(pFile != NULL)
    {
        fseek(pFile, 0L, SEEK_END);
        cantidad = ftell(pFile);
        pArchivo = malloc(cantidad);
        rewind(pFile);
        while(!feof(pFile))
        {
            auxInt = fread(pArchivo,sizeof(char),cantidad, pFile);
            if(auxInt != cantidad)
            {
                if(feof(pFile))
                {
                    break;
                }
            }
            else
            {
                printf("No se leyo el ultimo registro\n");
            }
        }
        *(pArchivo+cantidad) = 0;
    }
    return pArchivo;
}




/** \brief escribe en el archivo lo pasado por parametro
 *
 * \param FILE* pFile puntero al archivo donde va a escribir
 * \param char* texto lo que va a escribir
 * \return devuelve [0] si pudo escribir todo en el archivo, [-1] si hubo un error
 *
 */
int escribirEnArchivo(FILE* pFile, char* texto)
{
    int cantidad;
    int auxInt;
    int retorno =-1;
    if(pFile != NULL && texto != NULL)
    {
        cantidad = strlen(texto);
        auxInt = fwrite(texto, sizeof(char), cantidad, pFile);
        if(auxInt<cantidad)
        {
            printf("error!");
        }
        else
        {
            retorno = 0;
        }
    }
    return retorno;
}


/**
 *  Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 *  @param lista la lista de peliculas a ser agregadas en el archivo.
 *  @param nombre el nombre para el archivo.
 */
void generarPagina(EMovie* pMovie, int length)
{
    int i;
    char nombrePelicula[55];
    int auxInt;
    FILE* fHtml;
    FILE* fIndex1;
    FILE* fIndex2;
    char * pIndex1;
    char * pIndex2;

    if(pMovie != NULL && length>0)
    {
        do
        {
            auxInt = getStringSpace(nombrePelicula, "Ingrese el nombre de pagina: ", "ERROR Maximo 50 caracteres", 0, 51);
        }while(auxInt!=0);
        strcat(nombrePelicula, ".html");
        fHtml = fopen(nombrePelicula, "w");
        if(fHtml!= NULL)
        {
            fIndex1 = fopen("index1.html", "r");
            if(fIndex1 != NULL)
            {
                pIndex1 = leerArchivo(fIndex1);
                auxInt = escribirEnArchivo(fHtml, pIndex1);


                for(i= 0; i<length; i++)
                {
                    if((pMovie+i)->isEmpty == 0)
                    {
                    fprintf(fHtml, "\n\t\t\t<article class='col-md-4 article-intro'>\n");
                    fprintf(fHtml, "\t\t\t\t<a href='#'>\n");
                    fprintf(fHtml, "\t\t\t\t\t<img class='img-responsive img-rounded' src='http://%s'  alt=''>\n", (pMovie+i)->linkImagen);
                    fprintf(fHtml, "\t\t\t\t</a>\n");
                    fprintf(fHtml, "\t\t\t\t<h3>\n");
                    fprintf(fHtml, "\t\t\t\t\t<a href='#'>%s</a>\n",(pMovie+i)->titulo);
                    fprintf(fHtml, "\t\t\t\t</h3>\n");
                    fprintf(fHtml, "\t\t\t\t<ul>\n");
                    fprintf(fHtml, "\t\t\t\t\t<li>Genero: %s</li>\n",(pMovie+i)->genero);
                    fprintf(fHtml, "\t\t\t\t\t<li>Puntaje: %d</li>\n",(pMovie+i)->puntaje);
                    fprintf(fHtml, "\t\t\t\t\t<li>Duracion: %d</li>\n",(pMovie+i)->duracion);
                    fprintf(fHtml, "\t\t\t\t</ul>\n");
                    fprintf(fHtml, "\t\t\t\t<p>%s</p>\n",(pMovie+i)->descripcion);
                    fprintf(fHtml, "\t\t\t</article>\n");
                    }
                }
                fIndex2 = fopen("index2.html", "r");
                if(fIndex2 != NULL)
                {
                    pIndex2 = leerArchivo(fIndex2);
                    auxInt = escribirEnArchivo(fHtml, pIndex2);
                }
            }
        }
    }
    fclose(fHtml);
    fclose(fIndex1);
    fclose(fIndex2);
    free(pIndex1);
    free(pIndex2);
}
