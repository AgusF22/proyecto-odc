//#define TESTING
#ifdef TESTING
    #include <string.h>
#endif // TESTING

#include <stdio.h>
#include <stdlib.h>
#include "argumentparser.h"
#include "baseconverter.h"

int* helpArgPresent;            /**< @brief Pointer to integer, to store 1 if the help argument is present, 0 if not.*/
int* viewArgPresent;            /**< @brief Pointer to integer, to store 1 if the view argument is present, 0 if not.*/

char* numberArgIntegerValue;    /**< @brief Char array, the value of the integer part of the number argument.*/
char* numberArgFractionValue;   /**< @brief Char array, the value of the fractional part of the number argument.*/
int* sourceArgValue;            /**< @brief Pointer to integer, the value of the source base argument.*/
int* destArgValue;              /**< @brief Pointer to integer, the value of the destination base argument.*/

/**
* @brief Frees all the the global variables.
*/
void freeAll(){
    free(helpArgPresent);
    free(viewArgPresent);

    free(numberArgIntegerValue);
    free(numberArgFractionValue);
    free(sourceArgValue);
    free(destArgValue);
}

/**
* @brief Prints to the console the convert program help message.
*/
void showHelp(){
    printf("\n");
    printf("convert -n <number> [-s <source_base>] [-d <dest_base>] [-v] [-h]\n");
    printf("\n");
    printf("Description:\n");
    printf("\tThis tool is used to convert numbers between different bases. Allowed bases are in the range [2, 16].\n");
    printf("\n");
    printf("Parameter list:\n");
    printf("%4s\t%-11s\t%s\n\n", "-n", "number"       , "Specifies the number to convert. If it is not in base 10, -s argument must be specified.");
    printf("%4s\t%-11s\t%s\n\n", "-s", "source_base"  , "Specifies the source base.");
    printf("%4s\t%-11s\t%s\n\n", "-d", "dest_base"    , "Specifies the destination base.");
    printf("%4s\t%-11s\t%s\n\n", "-v", ""             , "Tells the program to show the calculation steps.");
    printf("%4s\t%-11s\t%s\n", "-h", ""             , "Shows this help message.");
    printf("\n");
    printf("%3sNOTE\n", "");
    printf("%3s----\n", "");
    printf("%3sThis program represents numbers with 10 precision digits for the integer part, and 5 for the fractional part.\n", "");
    printf("%3sThe conversion will fail if the outcome has more that 10 digits.\n", "");
}

#ifndef TESTING

/**
* @brief Main function of the convert program.
* @param argc Amount of arguments.
* @param argv Array of strings, the arguments for the execution.
*/
int main(int argc, char* argv[]){
    helpArgPresent = (int*)malloc(sizeof(int));
    viewArgPresent = (int*)malloc(sizeof(int));

    numberArgIntegerValue = (char*)malloc(sizeof(char) * 100);
    numberArgFractionValue = (char*)malloc(sizeof(char) * 50);
    sourceArgValue = (int*)malloc(sizeof(int));
    destArgValue = (int*)malloc(sizeof(int));

    long long* base10IntegerN;
    float* base10FractionalN;
    char* convertedIntegerN;
    char* convertedFractionalN;

    parseArguments(&argc, argv);

    if (*helpArgPresent) {
        showHelp();
    } else {
        if (*sourceArgValue == *destArgValue) {
            printf("Result: %s.%s\n", numberArgIntegerValue, numberArgFractionValue);
        } else {
            base10IntegerN = integerMultiplicationMethod(numberArgIntegerValue, sourceArgValue, viewArgPresent);
            convertedIntegerN = integerDivisionMethod(base10IntegerN, destArgValue, viewArgPresent);
            free(base10IntegerN);

            base10FractionalN = fractionDivisionMethod(numberArgFractionValue, sourceArgValue, viewArgPresent);
            convertedFractionalN = fractionMultiplicationMethod(base10FractionalN, destArgValue, viewArgPresent);
            free(base10FractionalN);

            printf("Result: %s.%s\n", convertedIntegerN, convertedFractionalN);
            free(convertedIntegerN);
            free(convertedFractionalN);
        }
    }

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
