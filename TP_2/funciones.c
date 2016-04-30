#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funciones.h"

/** \brief Inicializa el array,  le da valor 0 a todas variable estado del array.
 *
 * \param lista el array se pasa como parametro
 * \param cantidadItems la cantidad total de items
 *
 */
void initArray( EPersona lista[],int cantidadItems)
{
    int i;
    for(i=0; i<cantidadItems; i++)
    {
        lista[i].estado = 0;
    }
}


/**
 * Obtiene el primer indice libre del array.
 * @param lista el array se pasa como parametro.
 * @param cantidadItems la cantidad total de items
 * @return el primer indice disponible o [-1] si no hay espacio libre
 */
int obtenerEspacioLibre(EPersona lista[],int cantidadItems)
{
    int index = -1;
    int i;

    for(i= 0; i<cantidadItems; i++)
    {
        if(lista[i].estado == 0)
        {
            index = i;
            break;
        }
    }

    return index;
}


/**
* \brief Solicita un número al usuario y lo valida
* \param input Se carga el numero ingresado
* \param message Es el mensaje a ser mostrado
* \param eMessage Es el mensaje a ser mostrado en caso de error
* \param lowLimit Limite inferior a validar
* \param hiLimit Limite superior a validar
* \return Si obtuvo el numero [0] si no [-1]
*/
int getInt(int* input,char message[],char eMessage[], int lowLimit, int hiLimit)
{
    int auxInt;
    int flag = -1;
    int resp;
    printf("%s", message);
    fflush(stdin);          // Se pone bandera por si nos olvidamos un return
    resp = scanf("%d", &auxInt);
    if(resp == 1)
    {
        if(auxInt > lowLimit && auxInt < hiLimit)
        {
            *input = auxInt;
            flag = 0;
        }
    }
    if(flag == -1)
    {
        system("cls");
        printf("%s", eMessage);
    }
    return flag;
}


/**
* \brief Solicita una cadena de caracteres de solo letras y la valida
* \param input Se carga el string ingresado
* \param message Es el mensaje a ser mostrado
* \param eMessage Es el mensaje a ser mostrado en caso de error
* \param lowLimit Longitud mínima de la cadena
* \param hiLimit Longitud máxima de la cadena
* \return Si obtuvo la cadena [0] si no [-1]
*
*/
int getName(char* input,char message[],char eMessage[], int lowLimit, int hiLimit)
{
    char auxChar[50];
    int resp;
    int flagName = 1;
    int i;
    printf("%s", message);
    fflush(stdin);
    resp = scanf("%s", auxChar);
    if(resp == 1 && (strlen(auxChar)>lowLimit && strlen(auxChar) < hiLimit ) )
    {
        for(i= 0; i< strlen(auxChar); i ++)
        {
            auxChar[i] = tolower(auxChar[i]);
            if(auxChar[i] < 'a' || auxChar[i] >'z')
            {
                flagName = 0;
                break;
            }
        }
    }
    else
    {
        flagName = 0;
    }
    if(flagName)
    {
        auxChar[0] = toupper(auxChar[0]);
        strcpy(input, auxChar);
        return 0;
    }

    system("cls");
    printf("%s", eMessage);
    return -1;
}


/** \brief carga los datos pasados por parametro a un elemento del array
 *
 * \param edad la edad de tipo entera se pasa como parametro
 * \param dni el dni de tipo entera se pasa como parametro
 * \param nombre se para por parametro
 * \return una variable del tipo Epersona con los campos completos
 *
 */
EPersona cargarPersona(int edad, int dni, char nombre[])
{
    EPersona auxPersona;

    auxPersona.edad = edad;
    auxPersona.dni = dni;
    strcpy(auxPersona.nombre, nombre);
    auxPersona.estado = 1;

    return auxPersona;
}


/**
 * Obtiene el indice que coincide con el dni pasado por parametro.
 * @param lista el array se pasa como parametro.
 * @param dni el dni a ser buscado en el array.
 * @param cantidadItems la cantidad total de items
 * @return el indice en donde se encuentra el elemento que coincide con el parametro dni
   o [-1] si no existe.
 */
int buscarPorDni(EPersona lista[], int cantidadItems, int dni)
{
    int i;
    int index = -1;
    for(i=0;i<cantidadItems; i++)
    {
        if(lista[i].dni == dni)
        {
            index = i;
            break;
        }
    }
    return index;
}


/** \brief Muestra los datos de  persona
 *
 * \param persona una variable de tipo EPersona con los datos llenos
 * \return Nada, imprime (si estan llenos los campos) por pantalla los datos del campo
 *
 */
void mostrarUna(EPersona persona)
{
    if(persona.estado == 1)
    {
        printf("%s--%d--%d--\n", persona.nombre, persona.edad, persona.dni);
    }
    else
    {
        printf("Esa persona no existe!");
    }
}


/** \brief Muestra los datos del array lista
 *
 * \param lista array que contiene los datos a ser mostrados
 * \param cantidadItems la cantidad de items que tiene el array
 * \return Nada, imprime (si estan llenos los campos) por pantalla los datos del array
 *
 */
void mostrarPersonas(EPersona lista[], int cantidadItems)
{
    int i;
    for(i= 0; i<cantidadItems;i++)
    {
        if(lista[i].estado == 1)
        {
            mostrarUna(lista[i]);
        }
    }
}


/** \brief ordena por nombre los elementos del array
 *
 * \param lista array de los datos a ser ordenamos
 * \param cantidadItems la cantidad de items que tiene el array
 * \return Nada, ordena los elementos del array por nombre
 *
 */
void ordenarPorNombre(EPersona lista[], int cantidadItems)
{
    int i,j;
    EPersona auxPersona;

    for(i= 0; i<cantidadItems-1; i++)
    {
        for(j= i+1; j<cantidadItems; j++)
        {
            if(strcmp(lista[i].nombre, lista[j].nombre)== 1)
            {
                auxPersona = lista[i];
                lista[i] = lista[j];
                lista[j] = auxPersona;
            }
        }
    }
}


/** \brief segun el indice que se le da por parametro, borra un elemento
 *
 * \param lista array donde busca el elemento a ser borrado
 * \param indice de los datos que van a ser borrados
 * \return Nada, borra el elemento segun el indice
 *
 */
void borrarPersona(EPersona lista[], int indice)
{
    int opcion;
    int auxInt;
    printf("Nombre\t\tEdad\t\tDNI\n");
    mostrarUna(lista[indice]);
    auxInt = getInt(&opcion,"Desea borrar a esa persona?\n1-Si\n2-No\n", "Opcion no valida", 0, 3);
    if(auxInt != -1)
    {
        if(opcion == 1)
        {
            lista[indice].estado = 0;
            printf("Persona borrada exitosamente!\n");
        }
        else
        {
        printf("Accion cancelada\n");
        }
    }

}


/** \brief segun el indice que se le da por parametro, borra un elemento
 *
 * \param lista array donde busca el elemento a ser borrado
 * \param indice de los datos que van a ser borrados
 * \return Nada, borra el elemento segun el indice
 *
 */
void pedirDatos(int* edad, int* dni,char* nombre)
{
    int auxInt;
    int auxEdad;
    int auxDni;
    char auxNombre[50];
    do
    {
        auxInt = getName(auxNombre, "Ingrese su nombre: ", "ERROR: solo se permiten letras\n", 2, 50);
    }while(auxInt!=0);
    strcpy(nombre, auxNombre);

    do
    {
        auxInt = getInt(&auxEdad,"Ingrese su edad: ", "ERROR: solo se permiten numeros entre 2 y 99\n", 2,99);
    }while(auxInt!=0);
    *edad = auxEdad;

    do
    {
        auxInt = getInt(&auxDni,"Ingrese su DNI: ", "ERROR: Ingrese el DNI sin .\n", 0,99999999);
    }while(auxInt!=0);
    *dni = auxDni;

}


/** \brief Extrae las edades de un array de estructuras y los guarda en un array de enteros
 *
 * \param lista De donde extrae los datos
 * \param edades array de enteros donde guarda los datos
 * \param cantidadItems la cantidad de items que tiene el array
 * \return Nada, solamente guarda los datos en el array edades
 *
 */
void extraerDatosEdades(EPersona lista[], int edades[],int cantidadItems)
{
    int i;
    int menoresDieciocho = 0;
    int DiecinueveYtreintaCinco = 0;
    int mayoresTreintaCinco = 0;
    for(i=0; i<cantidadItems; i++)
    {
        if(lista[i].estado == 1)
        {
            if(lista[i].edad < 18)
            {
                menoresDieciocho = menoresDieciocho + 1;
            }
            else if(lista[i].edad > 35)
            {
                mayoresTreintaCinco = mayoresTreintaCinco + 1;
            }
            else
            {
                DiecinueveYtreintaCinco = DiecinueveYtreintaCinco + 1;
            }
        }
    }
    edades[0] = menoresDieciocho;
    edades[1] = DiecinueveYtreintaCinco;
    edades[2] = mayoresTreintaCinco;
}


/** \brief Crea un grafico a partir de los datos pasados por parametros
 * \param edades array que utiliza para crear el grafico
 * \return Nada, imprime por pantalla el grafico.
 *
 */
void crearGrafico(int edades[])
{
    int i;
    int j;
    int max = 0;
    int flagPrimera;

    for (i = 0; i < 3; i++)
    {
        if(edades[i] > max)
        {
            max = edades[i];
        }
    }

    for (i = max; i > 0; i--)
    {
        flagPrimera = 1;
        for (j = 0; j < 3; j++)
        {


            if (edades[j] >= i && flagPrimera)
            {
                printf("%02d| * ", i);
            }
            else if(edades[j] >= i)
            {
                printf("   * ");
            }
            else
            {
                printf("     ");
            }
            flagPrimera = 0;
        }

    putchar('\n');
    }
    printf("--+-------------\n\n");
    printf(" < 18  19-35  >35\n");


}
