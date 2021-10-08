#define TESTING

#include<math.h>

void digitChar(int* num, char* toReturn) {
    switch (*num) {
    case 10 ... 15:     *toReturn = *num + 55;
        break;
    case 0 ... 9:       *toReturn = *num + 48;
        break;
    default:
        *toReturn = 0;
    }
}

void digitValue(char* num, int* digInt) {
    switch (*num) {
    case 'A' ... 'F':
        *digInt = *num - 55;
        break;
    case 48 ... 57:
        *digInt = *num - 48;
        break;
    default:
        *digInt = 0;
    }
}

int* integerMultiplicationMethod(char* source, int* sourceLenght, int* sourceBase, int* viewArgument){
    // metodo de la multiplicacion para enteros (de base sourceBase a base 10)

    int* toReturn = (int*)malloc(sizeof(int));
    int* i = (int*) malloc(sizeof(int));
    int* digInt = (int*) malloc(sizeof(int));
    int* position = (int*) malloc(sizeof(int));
    double* calcAux = (double*) malloc(sizeof(double));
    *toReturn = 0;
    *calcAux =  0;
    *digInt  =  0;
    *position = 0;

    for (*i = 0; *i < *sourceLenght; (*i)++) {
        digitValue(&source[*i], digInt);
        *position = *sourceLenght - (*i + 1);
        *calcAux += *digInt * pow(*sourceBase, *position);

        if (*viewArgument == 1) {
            printf("%d + %d * (%d exp %d) = %.0f\n", *toReturn, *digInt, *sourceBase, *position, *calcAux);
        }
        *toReturn = (int) *calcAux;
    }

    free(i);
    free(digInt);
    free(position);
    free(calcAux);

    return toReturn;
}

char* integerDivisionMethod(int* source, int* destBase, int* viewArgument){
    // metodo de la division para enteros (de base 10 a base destBase)

    char* toReturn = (char*)malloc(sizeof(char) * 10);
    char* arrayAux = (char*)malloc(sizeof(char) * 10);
    int* i = (int*) malloc(sizeof(int));
    int* j = (int*) malloc(sizeof(int));
    float* quotient = (float*) malloc(sizeof(float));
    int* rest = (int*) malloc(sizeof(int));
    *quotient = 0; *rest = 0; *i = 0;*j = 0;

    do {
        *quotient = *source / *destBase;
        *rest = *source % *destBase;

        digitChar(rest, &arrayAux[*i]);
        if (*viewArgument == 1)
            printf("%d / %d = %.0f, rest = (%d)10 = (%c)%d\n", *source, *destBase, *quotient, *rest, arrayAux[*i], *destBase);

        *source = *quotient;
    //    digitChar(rest, &arrayAux[*i]);
        (*i)++;
    } while (*source != 0); //*source >= *destBase

    //digitChar(source, &arrayAux[*i]); //add last quotient
    //(*i)++;
    arrayAux[*i] = '\0';

    while (*i > 0) {
        toReturn[*j] = arrayAux[(*i)-1];
        #if 0
        #ifdef TESTING
        printf("array: %c:  --- return: %c\n", arrayAux[*i-1], toReturn[*j]);
        #endif // TESTING
        #endif
        (*i)--;
        (*j)++;
    }
    toReturn[*j] = '\0';

    #if 0
    #ifdef TESTING
    for(*i = 0; *i < *j; (*i)++)
        printf("toReturn: %c\n", toReturn[*i]);
    #endif // TESTING
    #endif

    free(i);
    free(quotient);
    free(rest);
    free(arrayAux);

    return toReturn;
}

char* fractionMultiplicationMethod(float* source, int* destBase, int* viewArgument){
    // metodo de la multiplicacion para fraccionarios (de base 10 a base destBase)

    char* toReturn = (char*)malloc(sizeof(char) * 5);
    int* i = (int*) malloc(sizeof(int));
    float* calcAux = (float*) malloc(sizeof(float));
    int* truncated = (int*) malloc(sizeof(int));

    for (*i = 0; *i < 5; (*i)++) {
        *calcAux = *source * *destBase;
        *truncated = trunc(*calcAux);
        digitChar(truncated, &toReturn[*i]);

        if (*viewArgument == 1) {
            printf("%.5f * %d = %.5f\n", *source, *destBase, *calcAux);
        }

        *source = *calcAux - trunc(*calcAux);
    }
    toReturn[*i] = '\0';
    return toReturn;
}

float* fractionDivisionMethod(char* source, int* sourceLenght, int* sourceBase, int* viewArgument) {
    // metodo de la division para fraccionarios (de base sourceBase a base 10)

    float* toReturn = (float*)malloc(sizeof(float));

    int* i = (int*) malloc(sizeof(int));
    char* digChar = (char*) malloc(sizeof(char));
    int* digInt = (int*) malloc(sizeof(int));
    float* quotient = (float*) malloc(sizeof(float));
    *quotient = 0;

    for (*i = 0; *i < *sourceLenght; (*i)++) {
        *digChar = source[*sourceLenght - (*i + 1)];
        digitValue(digChar, digInt);
        *quotient = (*quotient + *digInt) / *sourceBase;

        if (*viewArgument == 1) {
            printf("(%.5f + %d) / 10 = %.6f\n", *toReturn, *digInt, *quotient); //TODO redondear o truncar?
        }
        *toReturn = *quotient;
    }

    free(i);
    free(digChar);
    free(digInt);
    free(quotient);

    return toReturn;
}
