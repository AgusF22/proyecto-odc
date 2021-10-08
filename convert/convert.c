#define TESTING

#include <stdio.h>
#include <stdlib.h>
#include "argumentparser.h"
#include "baseconverter.h"

int* helpArgPresent;
int* viewArgPresent;

char* numberArgIntegerValue;
char* numberArgFractionValue;
int* sourceArgValue;
int* destArgValue;

void freeAll(){
    free(helpArgPresent);
    free(viewArgPresent);

    free(numberArgIntegerValue);
    free(numberArgFractionValue);
    free(sourceArgValue);
    free(destArgValue);
}

#ifndef TESTING

int main(int argc, char* argv[]){
    helpArgPresent = (int*)malloc(sizeof(int));
    viewArgPresent = (int*)malloc(sizeof(int));

    numberArgIntegerValue = (char*)malloc(sizeof(char) * 100);
    numberArgFractionValue = (char*)malloc(sizeof(char) * 50);
    sourceArgValue = (int*)malloc(sizeof(int));
    destArgValue = (int*)malloc(sizeof(int));

    parseArguments(&argc, argv);

    freeAll();

    return EXIT_SUCCESS;
}

#endif // TESTING

#ifdef TESTING

void printArgVarValues(){
    printf("\n");
    printf("numberArgIntegerValue   = %s\n", numberArgIntegerValue);
    printf("numberArgFractionValue  = %s\n", numberArgFractionValue);
    printf("sourceArgValue          = %d\n", *sourceArgValue);
    printf("destArgValue            = %d\n", *destArgValue);
    printf("helpArgPresent          = %d\n", *helpArgPresent);
    printf("viewArgPresent          = %d\n", *viewArgPresent);
    printf("\n");
}

int main(int argc, char* argv[]){
    helpArgPresent = (int*)malloc(sizeof(int));
    viewArgPresent = (int*)malloc(sizeof(int));

    numberArgIntegerValue = (char*)malloc(sizeof(char) * 100);
    numberArgFractionValue = (char*)malloc(sizeof(char) * 50);
    sourceArgValue = (int*)malloc(sizeof(int));
    destArgValue = (int*)malloc(sizeof(int));

    int* sourceBase10 = (int*)malloc(sizeof(int));
    char* sourceDest = (char*)malloc(sizeof(char));

    parseArguments(&argc, argv);

    printArgVarValues();

    //Save date the console
    char* argIntegerAux = (char*)malloc(sizeof(char));
    char* argFractionAux = (char*)malloc(sizeof(char));

    for(int i=0; numberArgIntegerValue[i] != '\0'; i++)
        argIntegerAux[i] = numberArgIntegerValue[i];

    for(int i=0; numberArgFractionValue[i] != '\0'; i++)
        argFractionAux[i] = numberArgFractionValue[i];

    //TESTING INTEGER METHODS

    printf("Metodo de la multiplicacion de interos:\n");
    int leng = strlen(numberArgIntegerValue);
    sourceBase10 = integerMultiplicationMethod(numberArgIntegerValue, &leng , sourceArgValue, viewArgPresent);

    printf("num en 10: %d ", *sourceBase10);

    //**************************************************************************************

    printf("\n\n");

    printf("Metodo de la division de enteros:\n");

    sourceDest = integerDivisionMethod(sourceBase10, destArgValue, viewArgPresent);

    printf("en base %d: ", *destArgValue);

    for(int j=0; sourceDest[j] != '\0'; j++)
        printf("%c", sourceDest[j]);

    //**************************************************************************************
    //TESTING FRACTIONARI METHOD

    printf("\n\n");

    printf("Metodo de la division de fraccionarios:\n");

    float* fracBaseOrigin = (float*)malloc(sizeof(float));
    int lengFrac = strlen(numberArgFractionValue);

    fracBaseOrigin = fractionDivisionMethod(numberArgFractionValue, &lengFrac, sourceArgValue, viewArgPresent);

    printf("\nfraccionario a base 10: %.5f", *fracBaseOrigin);

    //**************************************************************************************

    printf("\n\n");

    printf("Metodo de la multiplicacion de fraccionarios:\n");

    char* fracBase10 = (char*)malloc(sizeof(char));
    float* fracBaseAux = (float*)malloc(sizeof(float));
    *fracBaseAux = *fracBaseOrigin;

    fracBase10 = fractionMultiplicationMethod(fracBaseAux, destArgValue, viewArgPresent);

    printf("(%.5f)10 en base %d: ", *fracBaseOrigin, *destArgValue);

    for(int i = 0; fracBase10[i] != '\0'; i++)
        printf("%c", fracBase10[i]);


    freeAll();

    printf("\n\n");

    //**************************************************************************************

    printf("RESULTADO DE LA CONVERSION: ");

    printf("(");
    for(int j=0; argIntegerAux[j] != '\0'; j++)
        printf("%c", argIntegerAux[j]);
    printf(".");
    for(int i = 0; argFractionAux[i] != '\0'; i++)
        printf("%c", argFractionAux[i]);
    printf(")%d", *sourceArgValue);
    printf(" = (");
    for(int j=0; sourceDest[j] != '\0'; j++)
        printf("%c", sourceDest[j]);
    printf(".");
    for(int i = 0; fracBase10[i] != '\0'; i++)
        printf("%c", fracBase10[i]);
    printf(")%d", *destArgValue);

    printf("\n\n");

    return EXIT_SUCCESS;
}

#endif // TESTING
