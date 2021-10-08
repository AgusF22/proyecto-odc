//#define TESTING
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

void showHelp(){
    printf("HELP\n");
}

#ifndef TESTING

int main(int argc, char* argv[]){
    helpArgPresent = (int*)malloc(sizeof(int));
    viewArgPresent = (int*)malloc(sizeof(int));

    numberArgIntegerValue = (char*)malloc(sizeof(char) * 100);
    numberArgFractionValue = (char*)malloc(sizeof(char) * 50);
    sourceArgValue = (int*)malloc(sizeof(int));
    destArgValue = (int*)malloc(sizeof(int));

    int* base10IntegerN;
    int* base10FractionalN;
    char* convertedIntegerN;
    char* convertedFractionalN;

    parseArguments(&argc, argv);

    if (*helpArgPresent) {
        showHelp();
    } else {
        if (*sourceArgValue == *destArgValue) {
            printf("%s.%s\n", numberArgIntegerValue, numberArgFractionValue);
        } else {
            base10IntegerN = integerMultiplicationMethod(numberArgIntegerValue, sourceArgValue, viewArgPresent);
            convertedIntegerN = integerDivisionMethod(base10IntegerN, destArgValue, viewArgPresent);

            base10FractionalN = fractionDivisionMethod(numberArgFractionValue, sourceArgValue, viewArgPresent);
            convertedFractionalN = fractionMultiplicationMethod(base10FractionalN, destArgValue, viewArgPresent);

            printf("%s.%s\n", convertedIntegerN, convertedFractionalN);
        }
    }

    free(base10IntegerN);
    free(base10FractionalN);
    free(convertedIntegerN);
    free(convertedFractionalN);
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

    long long* sourceBase10 = (long long*)malloc(sizeof(long long));
    char* sourceDest = (char*)malloc(sizeof(char));

    printf("******************Start parse arguments test**********************************\n\n");

    parseArguments(&argc, argv);    // Test parseArguments

    printArgVarValues();            // Print arguments

    printf("\n********************End parse arguments test**********************************\n\n");


    //TESTING INTEGER METHODS

    printf("******************Start integer multiplication method test**********************************\n\n");

    sourceBase10 = integerMultiplicationMethod(numberArgIntegerValue, sourceArgValue, viewArgPresent);

    printf("num en 10 = %I64d \n", *sourceBase10);

    printf("\n********************End integer multiplication method test**********************************\n\n");

    /***************************************************************************************************************************************/

    printf("******************Start integer division method test**********************************\n\n");

    sourceDest = integerDivisionMethod(sourceBase10, destArgValue, viewArgPresent);

    printf("en base %d = %s", *destArgValue, sourceDest);

    printf("\n");

    printf("\n********************End integer division method test**********************************\n\n");

    /***************************************************************************************************************************************/

    printf("******************Start fractional division method test**********************************\n\n");

    float* fracBaseOrigin = (float*)malloc(sizeof(float));

    fracBaseOrigin = fractionDivisionMethod(numberArgFractionValue, sourceArgValue, viewArgPresent);

    printf("fraccionario a base 10 = %.5f\n", *fracBaseOrigin);

    printf("\n********************End fractional division method test**********************************\n\n");

    /***************************************************************************************************************************************/

    printf("******************Start fractional multiplication method test**********************************\n\n");

    char* fracBase10 = (char*)malloc(sizeof(char));
    float* fracBaseAux = (float*)malloc(sizeof(float));
    *fracBaseAux = *fracBaseOrigin;

    fracBase10 = fractionMultiplicationMethod(fracBaseAux, destArgValue, viewArgPresent);

    printf("(%.5f)10 en base %d = 0.%s\n", *fracBaseOrigin, *destArgValue, fracBase10);


    freeAll();

    printf("\n********************End fractional multiplication method test**********************************\n\n");

    /***************************************************************************************************************************************/

    printf("RESULTADO DE LA CONVERSION: ");

    printf("(%s.%s)%d = ",numberArgIntegerValue,numberArgFractionValue,*sourceArgValue);
    printf("(%s.%s)%d", sourceDest, fracBase10, *destArgValue);

    printf("\n\n");

    return EXIT_SUCCESS;
}

#endif // TESTING
