#include<math.h>

void encode(int* num, char* toReturn) {
     switch(*num) {
    case 97 ... 102:    *toReturn += 32;
    case 65 ... 70:     *toReturn += 7;
        break;
    default:
        case 0 ... 9:     *toReturn += 48;
    }
}

void decode(char* num, int* digInt) {
    switch(*num) {
    case 97 ... 102:    *digInt -= 32;
    case 65 ... 70:     *digInt -= 7;
        break;
    default:
        case 48 ... 57:     *digInt -= 48;
    }
}

int* integerMultiplicationMethod(char* source, int* sourceLenght, int* sourceBase, int* viewArgument){
    // metodo de la multiplicacion para enteros (de base sourceBase a base 10)

    int* toReturn = (int*)malloc(sizeof(int));
    int* i = (int*) malloc(sizeof(int));
    int* digInt = (int*) malloc(sizeof(int));
    int* position = (int*) malloc(sizeof(int));
    double* calcAux = (double*) malloc(sizeof(double));
    *calcAux = 0;

    for(*i = 0; *i < *sourceLenght; (*i)++) {
        decode(&source[*i], digInt);
        *position = *sourceLenght - (*i + 1);
        *calcAux = *digInt * pow(*sourceBase, *position);

        if(*viewArgument == 1) printf("%f + %d * (%d exp %d)", *calcAux, *digInt, *sourceBase, *position);
        *toReturn += (int) *calcAux;
    }

    free(i);
    free(digInt);
    free(position);
    free(calcAux);

    return toReturn;
}

char* integerDivisionMethod(int* source, int* sourceLenght, int* destBase, int* viewArgument){
    // metodo de la division para enteros (de base 10 a base destBase)

    char* toReturn = (char*)malloc(sizeof(char) * 10);
    int* i = (int*) malloc(sizeof(int));
    float* quotient = (float*) malloc(sizeof(float));
    int* rest = (int*) malloc(sizeof(int));
    *quotient = 0; *rest = 0;

    for (*i = 0; *i < *sourceLenght; (*i)++) {
        *quotient = *source / *destBase;
        *rest = *source % *destBase;

        if (*viewArgument == 1) printf("%d / %d = %f, rest: %d", *source, *destBase, *quotient, *rest);

        *source = *quotient;
        encode(rest, &toReturn[*i]);
    }

    free(i);
    free(quotient);
    free(rest);

    return toReturn;
}

char* fractionMultiplicationMethod(int* source, int* sourceLenght, int* destBase, int* viewArgument){
    // metodo de la multiplicacion para fraccionarios (de base 10 a base destBase)

    char* toReturn = (char*)malloc(sizeof(char) * 5);
    int* i = (int*) malloc(sizeof(int));
    float* calcAux = (float*) malloc(sizeof(float));


    for(*i = 0; *i <= 5; (*i)++) {
        *calcAux = (*source / 10) * *destBase;
        toReturn[*i] = trunc(*calcAux);

        if(*viewArgument == 1) printf("0.%d * %d = %d", *source, *destBase, *calcAux);

        *source = *calcAux - trunc(*calcAux);
    }
    return toReturn;
}

int* fractionDivisionMethod(char* source, int* sourceLenght, int* sourceBase, int* viewArgument){
    // metodo de la division para fraccionarios (de base sourceBase a base 10)

    int* toReturn = (int*)malloc(sizeof(int));
    int* i = (int*) malloc(sizeof(int));
    char* digChar = (char*) malloc(sizeof(char));
    int* digInt = (int*) malloc(sizeof(int));
    float* quotient = (float*) malloc(sizeof(float));
    *quotient = 0;

    for (*i = 0; *i < *sourceLenght; (*i)++) {
        *digChar = source[*sourceLenght - (*i + 1)];   //+1 o +2? por el '/0'
        decode(digChar, digInt);
        *toReturn = (*quotient + *digInt) / 10;

        if (*viewArgument == 1) printf("(%f + %d) / 10 = %d", *quotient, *digInt, *toReturn);
        *quotient = *toReturn;
    }

    free(i);
    free(digChar);
    free(digInt);
    free(quotient);

    return toReturn;
}
