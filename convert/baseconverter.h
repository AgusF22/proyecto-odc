#ifndef BASECONVERTER_H
#define BASECONVERTER_H

#include<math.h>

void digitChar(int* num, char* toReturn) {          // Codifica un numero a su respectiva representacion en ASCII.
    switch (*num) {                                 //10 ... 15 -> A ... F
    case 10 ... 15:     *toReturn = *num + 55;
        break;
    case 0 ... 9:       *toReturn = *num + 48;
        break;
    default:
        *toReturn = 0;                              //asigna 0 si los valores pasados por parametro no son correctos.
    }
}

void digitValue(char* num, int* digInt) {           // Decodifica un caracter a su respectivo valor numerico.
    switch (*num) {                                 //A ... F -> 10 ... 15
    case 'A' ... 'F':
        *digInt = *num - 55;
        break;
    case 48 ... 57:
        *digInt = *num - 48;
        break;
    default:
        *digInt = 0;                                //asigna 0 si los valores pasados por parametro no son correctos.
    }
}

int* isRepresentable(long long* num, int* baseDest) {       // Verifica si num es un valor representable en la base destino.
    int* aux = (int*) malloc(sizeof(int));

    if ( pow(*baseDest, 10) - 1 >= *num)                    //compara el maximo numero representable con num.
        *aux = 1;                                           // Representable.
    else
        *aux = 0;                                           //No representable.

    return aux;                                             //retorna 1 si es representable, 0 en caso contrario.
}


/*
 * metodo de la multiplicacion para enteros (de base sourceBase a base 10)
*/
long long* integerMultiplicationMethod(char* nInteger, int* sourceBase, int* viewArgument){

    char* nIntegerCopy = (char*) malloc(sizeof(char));                     //variable auxilar para manipular el string nInteger.
    long long* toReturn = (long long*)malloc(sizeof(long long));           //variable para almacena el valor que retorna el metodo.
    int* i = (int*) malloc(sizeof(int));                                   //Index para recorrer ciclos.
    int* digInt = (int*) malloc(sizeof(int));                              //variable para almacenar un caracter del string(nIntegerCopy).
    int* position = (int*) malloc(sizeof(int));                            //variable para almacenar la posicion de un caracter del string.
    long long* calcAux = (long long*) malloc(sizeof(long long));           //variable para almacenar el valor de la conversion hasta el momento.
    int* sourceLenght = (int*) malloc(sizeof(int));                        //variable para almacenar la longitud del string(nIntegerCopy).

    *sourceLenght = 0;                                                     //inicializa en 0 la longitud.

    for(*i = 0; nInteger[*i] != '\0'; (*i)++){                             //recorre nInteger hasta hallar el terminador
        nIntegerCopy[*i] = nInteger[*i];                                   //copia en nIntegerCopy los caracters de nInteger.
    }
    nIntegerCopy[*i] = '\0';                                               //agrega un terminador a nIntegerCopy.

    *sourceLenght = *i;                                                    //guarda la longitud de nIntegerCopy en sourceLength.

    *toReturn = 0;                                                         //inicializa en 0.
    *calcAux =  0;
    *digInt  =  0;
    *position = 0;                                                         //****************

    for (*i = 0; *i < *sourceLenght; (*i)++) {                             //recorre todo el string nIntegerCopy

        digitValue(&nIntegerCopy[*i], digInt);                             //guarda en digInt el valor numerico del caracter de nInteger en la posicion *i.
        *position = *sourceLenght - (*i + 1);                              //guarda las posicion del string, del ultimo al primer caracter.
        *calcAux += *digInt * pow(*sourceBase, *position);      //multiplica cada digito por su base elevado a su posicion relativa.

        if (*viewArgument == 1) {                                          //imprime por pantalla los pasos intermedios.
            printf("%*I64d  + %d * %d^%d = %I64d\n", *sourceLenght, *toReturn, *digInt, *sourceBase, *position, *calcAux);
        }
        *toReturn = *calcAux;                                 //asigna el valor actual de la conversion.
    }

    free(i);                                                  //libera la memoria dinamica usada.
    free(digInt);
    free(position);
    free(calcAux);
    free(nIntegerCopy);
    free(sourceLenght);

    return toReturn;                                          //retorna el numero ingresado en base 10.
}

/*
 * metodo de la division para enteros (de base 10 a base destBase)
*/
char* integerDivisionMethod(long long* nInteger, int* destBase, int* viewArgument){

    long long* nIntegerCopy = (long long*) malloc(sizeof(long long));     //variable auxilar para manipular el numero nInteger.
    char* toReturn = (char*)malloc(sizeof(char) * 10);                    //variable para almacena el valor que retorna el metodo.
    char* arrayAux = (char*)malloc(sizeof(char) * 10);                    //variable para almacenar el string a retornar en orden inverso.
    int* i = (int*) malloc(sizeof(int));                                  //Index para recorrer ciclos.
    int* j = (int*) malloc(sizeof(int));                                  //Index para recorrer ciclos.
    double* quotient = (double*) malloc(sizeof(double));                  //variable para almacenar el cociente de las divisiones.
    int* rest = (int*) malloc(sizeof(int));                               //variable para almacenar el resto de la divisiones.
    int* representable = (int*) malloc(sizeof(int));                      //variable para manejar magnitudes no representables.
    int* length = (int*) malloc(sizeof(int));                             //variable para almacenar la longitud del numero nIntegerCopy.
    *length = 0;                                                          //inicializa en 0 la longitud.

    *nIntegerCopy = *nInteger;                                            //copia el valor de nInteger en nIntegerCopy.

    while(*nIntegerCopy != 0) {                                           //calcula la longitud del numero nIntegerCopy.
        *nIntegerCopy /= 10;
        (*length)++;
    }

    *nIntegerCopy = *nInteger;                                            //vuelve a copiar el valor de nInteger en nIntegerCopy

    representable = isRepresentable(nIntegerCopy, destBase);              //verifica si el numero es representable en la base destino.

    if(*representable == 0) {                                             //si lo es representable, libera la memoria dinamica
        //free                                                            // y termina el programa con EXIT_FAILURE.
        free(i);
        free(quotient);
        free(rest);
        free(arrayAux);
        free(nIntegerCopy);
        free(representable);
        free(toReturn);
        freeAll();
        free(nInteger);
        free(length);

        exit(EXIT_FAILURE);
    }

    *quotient = 0;                                                      //inicializa variables en 0.
    *rest = 0;
    *i = 0;
    *j = 0;

    do {
        *quotient = (double)*nIntegerCopy / (double) *destBase;         //calcula el cociente entre nIntegerCopy y la base destino.
        *rest = *nIntegerCopy % *destBase;                              //calcula el resto entre nIntegerCopy y la base destino.
        *quotient = trunc(*quotient);                                   //trunca el valor del cociente, quotient conserva la parte entera.
        digitChar(rest, &arrayAux[*i]);                                 //almacena en arrayAux el resto calculado previamente.

        if (*viewArgument == 1)                                          //imprime por pantalla los pasos intermedios.
            printf("%*I64d / %d = %*.5lf, rest = (%d)10 = (%c)%d\n",
                *length, *nIntegerCopy, *length, *destBase, *quotient, *rest, arrayAux[*i], *destBase);

        *nIntegerCopy = (long long)*quotient;                            //almacena en nIntegerCopy el cociente truncado(parte entera).
        (*i)++;                                                          //incrementa el contador en 1.
    } while (*nIntegerCopy != 0);                                        //cicla hasta que nIntegerCopy sea 0(cuando el cociente sea 0).


    arrayAux[*i] = '\0';                                                 //agrega un terminador a arrayAux.

    while (*i > 0) {                                                     //copia en toReturn el arrayAux en orden inverso.
        toReturn[*j] = arrayAux[(*i)-1];
        #if 0
        #ifdef TESTING
        printf("array: %c:  --- return: %c\n", arrayAux[*i-1], toReturn[*j]);
        #endif // TESTING
        #endif
        (*i)--;
        (*j)++;
    }
    toReturn[*j] = '\0';                                                 //agrega un terminador a toReturn

    #if 0
    #ifdef TESTING
    for(*i = 0; *i < *j; (*i)++)
        printf("toReturn: %c\n", toReturn[*i]);
    #endif // TESTING
    #endif

    free(i);                                                            //libera la memoria dinamica.
    free(quotient);
    free(rest);
    free(arrayAux);
    free(nIntegerCopy);
    free(representable);
    free(length);

    return toReturn;                                                    //retorna el string con el numero en base destino.
}

/*
 * metodo de la multiplicacion para fraccionarios (de base 10 a base destBase)
*/
char* fractionMultiplicationMethod(float* nFraction, int* destBase, int* viewArgument){

    char* toReturn = (char*)malloc(sizeof(char) * 5);               //variable para almacenar el valor de retorno del metodo.
    int* i = (int*) malloc(sizeof(int));                            //index para recorrer ciclos.
    float* calcAux = (float*) malloc(sizeof(float));                //variable para almacenar calculos de pasos intermedios.
    int* truncated = (int*) malloc(sizeof(int));                    //varianle para amacenar un valor truncado.

    for (*i = 0; *i < 5; (*i)++) {                                  //ciclo de 5 repeticiones(una repeticion por cada digito).
        *calcAux = (*nFraction) * (*destBase);                      //calcula el producto entre el numero y la base destino.
        *truncated = truncf(*calcAux);                              //trunca calcAux para salvar la parte entera.
        digitChar(truncated, &toReturn[*i]);                        //almacena el valor truncado en el array de salida, en su respectiva codificacion.

        if (*viewArgument == 1) {                                   //muestra por pantalla los pasos intermedios.
            printf("%.5f * %d = %.5lf\n", *nFraction, *destBase, *calcAux);
        }

        *nFraction = *calcAux - truncf(*calcAux);                   //almacena en nFraction la parte fraccionaria de calcAux.
    }
    toReturn[*i] = '\0';                                            //agrega un terminador a toReturn.

    //free                                                          //libera la memoria dinamica.
    free(i);
    free(calcAux);
    free(truncated);
    freeAll();

    return toReturn;                                                //retorna el numero en base destino.
}


/*
 * metodo de la division para fraccionarios (de base sourceBase a base 10)
*/
float* fractionDivisionMethod(char* nFraction, int* sourceBase, int* viewArgument) {

    float* toReturn = (float*)malloc(sizeof(float));                //variable para almacenar el valor de retorno.
    int* i = (int*) malloc(sizeof(int));                            //index para recorrer ciclos.
    char* digChar = (char*) malloc(sizeof(char));                   //variable para almacenar un caracter del string nFraction.
    int* digInt = (int*) malloc(sizeof(int));                       //variable para almacenar un digito del numero nFraction.
    float* quotient = (float*) malloc(sizeof(float));               //variable para almacenar el cociente de divisiones a nFraction.
    int* length = (int*) malloc(sizeof(int));                       //variable para almacenar la longitud de nFraction.
    *quotient = 0;                                                  //inicializa en 0 las variables.
    *length = 0;

    for(*i = 0; nFraction[*i] != '\0'; (*i)++){                     //recorre nFraction para obtener su longitud.
        (*length)++;
    }

    for (*i = 0; *i < *length; (*i)++) {                            //recorre las posiciones de nFraction.
        *digChar = nFraction[*length - (*i + 1)];                   //almacena un caracter de nFraction. Comienza desde la ultima posicion.
        digitValue(digChar, digInt);                                //almacena en digInt el valor numerico de digChar.
        *quotient = (*quotient + *digInt) / *sourceBase;            //calcula la suma del cociente + digInt y los divide por su base.

        if (*viewArgument == 1) {                                   //muestra por pantalla los pasos intermedios.
            printf("(%.5f + %d) / 10 = %.6f\n", *toReturn, *digInt, *quotient);
        }
        *toReturn = *quotient;                                      //almacena en toReturn el cociente, antes de volver a ciclar.
    }

    free(i);                                                        //libera memoria dinamica.
    free(digChar);
    free(digInt);
    free(quotient);
    free(length);

    return toReturn;                                                //retorna el numero en base 10.
}

#endif // BASECONVERTER_H
