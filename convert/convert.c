#define TESTING
#ifdef TESTING
    #include <string.h>
#endif // TESTING

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

int main(int argc, char* argv[]){   // TESTING main
    helpArgPresent = (int*)malloc(sizeof(int));
    viewArgPresent = (int*)malloc(sizeof(int));

    numberArgIntegerValue = (char*)malloc(sizeof(char) * 100);
    numberArgFractionValue = (char*)malloc(sizeof(char) * 50);
    sourceArgValue = (int*)malloc(sizeof(int));
    destArgValue = (int*)malloc(sizeof(int));

    int* sourceBase10 = (int*)malloc(sizeof(int));
    char* sourceDest = (char*)malloc(sizeof(char));

    printf("******************Start parse arguments test**********************************\n\n");

    parseArguments(&argc, argv);    // Test parseArguments

    printArgVarValues();            // Print arguments

    printf("\n********************End parse arguments test**********************************\n\n");

    //Save date the console
    char* argIntegerAux = (char*)malloc(sizeof(char));
    char* argFractionAux = (char*)malloc(sizeof(char));

    for (int i = 0; numberArgIntegerValue[i] != '\0'; i++) {
        argIntegerAux[i] = numberArgIntegerValue[i];
    }

    for (int i = 0; numberArgFractionValue[i] != '\0'; i++) {
        argFractionAux[i] = numberArgFractionValue[i];
    }

    //TESTING INTEGER METHODS

    printf("******************Start integer multiplication method test**********************************\n\n");
    int leng = strlen(numberArgIntegerValue);
    sourceBase10 = integerMultiplicationMethod(numberArgIntegerValue, &leng , sourceArgValue, viewArgPresent);

    printf("num en 10 = %d \n", *sourceBase10);

    printf("\n********************End integer multiplication method test**********************************\n\n");

    /***************************************************************************************************************************************/

    printf("******************Start integer division method test**********************************\n\n");

    sourceDest = integerDivisionMethod(sourceBase10, destArgValue, viewArgPresent);

    printf("en base %d = ", *destArgValue);

    for(int j=0; sourceDest[j] != '\0'; j++) {
        printf("%c", sourceDest[j]);
    }
    printf("\n");

    printf("\n********************End integer division method test**********************************\n\n");

    /***************************************************************************************************************************************/

    printf("******************Start fractional division method test**********************************\n\n");

    float* fracBaseOrigin = (float*)malloc(sizeof(float));
    int lengFrac = strlen(numberArgFractionValue);

    fracBaseOrigin = fractionDivisionMethod(numberArgFractionValue, &lengFrac, sourceArgValue, viewArgPresent);

    printf("fraccionario a base 10 = %.5f\n", *fracBaseOrigin);

    printf("\n********************End fractional division method test**********************************\n\n");

    /***************************************************************************************************************************************/

    printf("******************Start fractional multiplication method test**********************************\n\n");

    char* fracBase10 = (char*)malloc(sizeof(char));
    float* fracBaseAux = (float*)malloc(sizeof(float));
    *fracBaseAux = *fracBaseOrigin;

    fracBase10 = fractionMultiplicationMethod(fracBaseAux, destArgValue, viewArgPresent);

    printf("(%.5f)10 en base %d = ", *fracBaseOrigin, *destArgValue);

    for(int i = 0; fracBase10[i] != '\0'; i++){
        printf("%c", fracBase10[i]);
    }
    printf("\n");

    freeAll();

    printf("\n********************End fractional multiplication method test**********************************\n\n");

    /***************************************************************************************************************************************/

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
