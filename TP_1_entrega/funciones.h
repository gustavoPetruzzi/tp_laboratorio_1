#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
/** \brief Solicita un numero al usuario
 *
 * \param
 * \param
 * \return devuelve el numero ingresado por el usuario
 *
 */
double ingresarNumero(void);



/** \brief suma 2 numeros y devuelve el resultado
 *
 * \param x Primer numero a sumar
 * \param y Segundo numero a sumar
 * \return Devuelve el resultado de la suma
 *
 */
float sum(double, double);



/** \brief resta 2 numeros y devuelve el resultado
 *
 * \param x Primer numero a sumar
 * \param y Segundo numero a sumar
 * \return Devuelve el resultado de la suma
 *
 */
float subtract(double, double);



/** \brief multiplica 2 numeros y devuelve el resultado
 *
 * \param x Primer numero a multiplicar
 * \param y Segundo numero a multiplicar
 * \return Devuelve el resultado de la multiplicacion
 *
 */
float multiply(double, double);



/** \brief divide 2 numeros y devuelve el resultado
 *
 * \param x Primer numero, dividendo
 * \param y Segundo numero, divisor
 * \return Devuelve el resultado de la division
 *
 */
float divide (double, double);



/** \brief Calcula el factorial de un numero ingresado en el parametro
 *
 * \param x Numero al cual se le calcula el factorial
 * \return Devuelve el factorial del numero ingresado como parametro
 *
 */
int factorial(int);



/** \brief Se ingresa un numero y devuelve si es un Float o no
 *
 * \param Se ingresa el numero que se quiere saber si es Float o no
 * \return Devuelve 1 si es Float o 0 si es Integer
 *
 */
int isFloat( float);



#endif // FUNCIONES_H_INCLUDED
