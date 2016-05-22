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
            fread(pMovie,sizeof(EMovie),length,pArch);

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
    if(pMovie != NULL && length> 0)
    {
        FILE *pArch;

            pArch=fopen("binMovie.dat","wb");
            if(pArch == NULL)
            {
                return 1;
            }

        fwrite(pMovie,sizeof(EMovie),length,pArch);

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
    char auxTitulo[20];
    int auxInt;
    if(pMovie != NULL && length> 0)
    {
        do
        {
            auxInt = getStringSpace(auxTitulo, "Ingrese el titulo de la pelicula: ", "Error: Maximo 50 caracteres", 0, 21);
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
 * \return [-1] si no pudo pedir los datos o [0] si pudo pedir los datos
 *
 */

int pedirDatos(EMovie* pMovie, int length, char* titulo, char* genero, int* duracion, char* descripcion, int* puntaje, char* linkImagen)
{
    char auxTitulo[50];
    char auxGenero[20];
    int auxDuracion;
    char auxDescripcion[50];
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
            for(i=0;i<length; i++)
                if(strcmp((pMovie+i)->titulo, auxTitulo) == 0)
                {
                    auxInt = -1;
                    printf("Ya existe una pelicula con ese titulo!");
                    break;
                }
        }while(auxInt!=0);
        strcpy(titulo, auxTitulo);

        do
        {
            auxInt = getStringSpace(auxGenero, "Ingrese el genero: ", "Error: Maximo 20 caracteres", 0, 21);
        }while(auxInt!=0);
        strcpy(genero, auxGenero);

        do
        {
            auxInt = getStringSpace(auxDescripcion, "Ingrese la descripcion: ", "Error: Maximo 100 caracteres", 0, 21);
        }while(auxInt!=0);
        strcpy(descripcion, auxDescripcion);

        do
        {
            auxInt = getString(auxLinkImagen, "Ingrese el link de la imagen: ", "Error: Maximo 100 caracteres", 0, 101);
        }while(auxInt!=0);
        strcpy(linkImagen, auxLinkImagen);

        do
        {
            auxInt = getInt(&auxDuracion, "Ingrese la duracion de la pelicula de la imagen: ", "Error: duracion minima 60 minutos", 59, 961);
            // VALIDO HASTA 961 MINUTOS PORQUE LA PELICULA MAS LARGA HASTA EL MOMENTO ES DE 15HS
        }while(auxInt!=0);
        *duracion = auxDuracion;

        do
        {
            auxInt = getInt(&auxPuntaje, "Ingrese el puntaje: ", "Error: puntaje valido del 1 al 10", 0, 11);
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

    strcpy(auxPelicula.titulo, titulo);
    strcpy(auxPelicula.genero, genero);
    auxPelicula.duracion = *duracion;
    strcpy(auxPelicula.descripcion, descripcion);
    auxPelicula.puntaje = *puntaje;
    strcpy(auxPelicula.linkImagen, linkImagen);
    auxPelicula.isEmpty = 0;

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
    char descripcion[50];
    int puntaje;
    char linkImagen[100];
    int auxInt;
    if(pMovie != NULL && length > 0)
    {
        retorno = 0;
        indice = buscarLibre(pMovie, length);
        if(indice !=-1)
        {
            auxInt = pedirDatos(pMovie, length, titulo, genero, &duracion, descripcion, &puntaje, linkImagen);
            if(auxInt == 0)
            {
                *(pMovie+indice) = cargarDatos(titulo, genero, &duracion, descripcion, &puntaje, linkImagen);
            }
            else
            {
                printf("No se ha podido cargar la pelicula");
            }
        }
        else
        {
            printf("No hay mas lugar para cargar peliculas");
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
                auxInt = siOno(&auxChar, "Desea borrar? s/n", "error: Ingrese 's' para borrar o 'n' para cancelar", 's', 'n');
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
            printf("No existe ninguna pelicula con ese nombre");
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
    char titulo[20];
    char genero[20];
    int duracion;
    char descripcion[50];
    int puntaje;
    char linkImagen[50];
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
                auxInt = siOno(&auxChar, "Desea modificar? s/n", "error: Ingrese 's' para borrar o 'n' para cancelar", 's', 'n');
            }while(auxInt !=0);
            if(auxChar == 's')
            {
                auxInt = pedirDatos(pMovie, length, titulo, genero, &duracion, descripcion, &puntaje, linkImagen);
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


/*
int mostrarEmpleado(EMovie* pMovie, int length)
{
    int i;
    int retorno = -1;
    if(pMovie !=NULL && length> 0)
    {
        retorno = 0;
        for(i=0;i<length;i++)
        {
            if((pMovie+i)->isEmpty == 0)
            {
                printf("Titulo\n\t%s\nDuracion\n\t%d min\nPuntaje\n\t%d pts\n", (pMovie+i)->titulo, (pMovie+i)->duracion, (pMovie+i)->puntaje);
                printf("______________________________________________________\n");
            }
        }
    }
    return retorno;
}
*/
/*

int abrirArchivo(FILE* pArch, char* nombre, char* index)
{
    int retorno = -1;
    int cantidad;
    int auxInt;
    char * auxChar;
    if(nombre != NULL)
    {
        pArch = fopen(nombre, "w");
        if(pArch != NULL)
        {
            fseek(pArch, 0L, SEEK_END);
            cantidad = ftell(pArch);
            auxChar = realloc(index, (sizeof(char) * cantidad));
            if(auxChar != NULL)
            {
                index = auxChar;
            }
            rewind(pArch);

            while(!feof(pArch))
            {
               auxInt = fread(index,sizeof(char),cantidad,pArch);
               if(auxInt!=cantidad)
               {
                   if(feof(pArch))
                   {
                       retorno = 0;
                       break;
                   }
                   else
                   {
                       printf("No se pudo leer el registro");
                   }
               }
            }
        }
    }
    return retorno;
}
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
        //printf("CANTIDAD = %d ", cantidad);
        pArchivo = malloc(cantidad);
        rewind(pFile);
        auxInt = fread(pArchivo,sizeof(char),cantidad, pFile);
        *(pArchivo+cantidad) = 0;
        //printf("\nTIENE QUE LEER: %d", auxInt);
    }
    return pArchivo;
}





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
            printf("success!");
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
            }
            /*
            fprintf(fHtml, "<!DOCTYPE html>\n");
            fprintf(fHtml, "<!-- Template by Quackit.com -->\n");
            fprintf(fHtml, "<html lang='en'>\n");
            fprintf(fHtml, "<head>\n");
            fprintf(fHtml, "\t<meta charset='utf-8'>\n");
            fprintf(fHtml, "\t<meta http-equiv='X-UA-Compatible' content='IE=edge'>\n");
            fprintf(fHtml, "\t<meta name='viewport' content='width=device-width, initial-scale=1'>\n");
            fprintf(fHtml, "\t<!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->\n");
            fprintf(fHtml, "\t<title>Lista peliculas</title>\n");
            fprintf(fHtml, "\t<!-- Bootstrap Core CSS -->\n");
            fprintf(fHtml, "\t<link href='css/bootstrap.min.css' rel='stylesheet'>\n");
            fprintf(fHtml, "\t<!-- Custom CSS: You can use this stylesheet to override any Bootstrap styles and/or apply your own styles -->\n");
            fprintf(fHtml, "\t<link href='css/custom.css' rel='stylesheet'>\n");
            fprintf(fHtml, "\t<!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->\n");
            fprintf(fHtml, "\t<!-- WARNING: Respond.js doesn't work if you view the page via file:// -->\n");
            fprintf(fHtml, "\t<!--[if lt IE 9]>\n");
            fprintf(fHtml, "\t\t<script src='https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js'></script>\n");
            fprintf(fHtml, "\t\t<script src='https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js'></script>\n");
            fprintf(fHtml, "\t<![endif]-->\n");
            fprintf(fHtml, "</head>\n");
            fprintf(fHtml, "<body>\n");
            fprintf(fHtml, "\t<div class='container'>\n");
            fprintf(fHtml, "\t\t<div class='row'>\n\n\n");
            */
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
                fprintf(fHtml, "\t\t\t\t\t<li>Genero:%s</li>\n",(pMovie+i)->genero);
                fprintf(fHtml, "\t\t\t\t\t<li>Puntaje:%d</li>\n",(pMovie+i)->puntaje);
                fprintf(fHtml, "\t\t\t\t\t<li>Duracion:%d</li>\n",(pMovie+i)->duracion);
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

            /*
            fprintf(fHtml, "\t\t</div>\n");
            fprintf(fHtml, "\t\t<!-- /.row -->\n");
            fprintf(fHtml, "\t</div>\n");
            fprintf(fHtml, "\t<!-- /.container -->\n");
            fprintf(fHtml, "\t<!-- jQuery -->\n");
            fprintf(fHtml, "\t<script src='js/jquery-1.11.3.min.js'></script>\n");
            fprintf(fHtml, "\t<!-- Bootstrap Core JavaScript -->\n");
            fprintf(fHtml, "\t<script src='js/bootstrap.min.js'></script>\n");
            fprintf(fHtml, "\t<!-- IE10 viewport bug workaround -->\n");
            fprintf(fHtml, "\t<script src='js/ie10-viewport-bug-workaround.js'></script>\n");
            fprintf(fHtml, "\t<!-- Placeholder Images -->\n");
            fprintf(fHtml, "\t<script src='js/holder.min.js'></script>\n");
            fprintf(fHtml, "</body>\n");
            fprintf(fHtml, "</html>\n");
            */
        }
    }
    fclose(fHtml);
    fclose(fIndex1);
    fclose(fIndex2);
}
