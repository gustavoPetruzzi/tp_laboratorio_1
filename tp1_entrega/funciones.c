#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double ingresarNumero(void)
{
    char number[125];
    float aux = 1;
    system("cls");
    printf("Ingrese un numero: ");
    gets(number);
    if(number[0]== '0')
    {
        return 0;
    }
    else
    {
        aux = atof(number);
        if(aux != 0)
        {
            return aux;
        }
        else
        {
            printf("\n--------ERROR: Ingrese una opcion valida---------\n\n");
            system("pause");
            return aux;
        }
    }

}

float sum(double x, double y)
{
    double resultado;
    resultado = x + y;
    return resultado;

}

float subtract(double x, double y)
{
    double resultado;
    resultado = x - y;
    return resultado;
}
float divide(double x, double y)
{
    double resultado;
    resultado = x / y;
    return resultado;
}

float multiply(double x, double y)
{
    double resultado;
    resultado = x * y;
    return resultado;
}

int factorial(int x)
{
    int respuesta;

    if(x==0)
    {
        return 1;
    }

    respuesta = x* factorial(x-1);
    return(respuesta);


}

int isFloat(float A)
{
    int B;
    float Z;

    B = (int) A;
    Z = A-B; // si Z == 0 no es un float
    if(Z != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
