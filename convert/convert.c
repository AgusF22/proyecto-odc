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
    printf("%4s\t%-11s\t%s\n\n", "-n", "number"         , "Specifies the number to convert. If it is not in base 10, -s argument must be specified.");
    printf("%4s\t%-11s\t%s\n\n", "-s", "source_base"    , "Specifies the source base.");
    printf("%4s\t%-11s\t%s\n\n", "-d", "dest_base"      , "Specifies the destination base.");
    printf("%4s\t%-11s\t%s\n\n", "-v", ""               , "Tells the program to show the calculation steps.");
    printf("%4s\t%-11s\t%s\n", "-h", ""                 , "Shows this help message.");
    printf("\n");
    printf("%3sNOTE\n", "");
    printf("%3s----\n", "");
    printf("%3sThis program represents numbers with 10 precision digits for the integer part, and 5 for the fractional part.\n", "");
    printf("%3sThe conversion will fail if the outcome has more that 10 digits.\n", "");
}

/**
* @brief Main function of the convert program.
* @param argc Amount of arguments.
* @param argv Array of strings, the arguments for the execution.
*/
int main(int argc, char* argv[]){
    helpArgPresent = (int*)malloc(sizeof(int));                         // ********************************************
    viewArgPresent = (int*)malloc(sizeof(int));                         // ********************************************
    numberArgIntegerValue = (char*)malloc(sizeof(char) * 100);          // Allocate dynamic memory for global variables
    numberArgFractionValue = (char*)malloc(sizeof(char) * 50);          // ********************************************
    sourceArgValue = (int*)malloc(sizeof(int));                         // ********************************************
    destArgValue = (int*)malloc(sizeof(int));                           // ********************************************

    long long* base10IntegerN;                                          // Pointer to store the intermediate base 10 integer conversion
    float* base10FractionalN;                                           // Pointer to store the intermediate base 10 fraction conversion
    char* convertedIntegerN;                                            // Pointer to store integer part of  the result
    char* convertedFractionalN;                                         // Pointer to store fractional part of  the result

    parseArguments(&argc, argv);                                        // Parse the input arguments. Program will exit here if any error occurs

    if (*helpArgPresent) {                                              // If argument -h is present
        showHelp();                                                         // show help message
    } else {                                                            // else
        if (*sourceArgValue == *destArgValue) {                             // if the source and destination base are the same
            printf("%s.%s\n", numberArgIntegerValue,
                   numberArgFractionValue);                                     // Show the input number as result, as no conversion is needed
        } else {                                                            // else
            base10IntegerN =                                                    // ***********************************
                integerMultiplicationMethod(numberArgIntegerValue,              // convert the integer part to base 10
                                            sourceArgValue, viewArgPresent);    // ***********************************

            if(*viewArgPresent == 1) printf("\n");                              // print end of line if showing process

            convertedIntegerN =                                                 // ****************************************
                integerDivisionMethod(base10IntegerN,                           // convert integer part to destination base
                                      destArgValue, viewArgPresent);            // ****************************************

            if(*viewArgPresent == 1) printf("\n");                              // print end of line if showing process

            free(base10IntegerN);                                               // free the integer base 10 intermediate result

            base10FractionalN =                                                 // **************************************
                fractionDivisionMethod(numberArgFractionValue,                  // convert the fractional part to base 10
                                       sourceArgValue, viewArgPresent);         // **************************************

            if(*viewArgPresent == 1) printf("\n");                              // print end of line if showing process

            convertedFractionalN =                                              // *******************************************
                fractionMultiplicationMethod(base10FractionalN,                 // convert fractional part to destination base
                                             destArgValue, viewArgPresent);     // *******************************************

            if(*viewArgPresent == 1) printf("\n");                              // print end of line if showing process

            free(base10FractionalN);                                            // free the fractional base 10 intermediate result

            if(*viewArgPresent == 1){                                           // If viewArgument is present
                printf("Result = ");                                                // print result specifier
            }
            printf("%s.%s\n", convertedIntegerN, convertedFractionalN);         // print result

            free(convertedIntegerN);                                            // Free dynamic memory
            free(convertedFractionalN);                                         // *******************
        }
    }

    freeAll();                                                          // Free global variables dynamic memory

    return EXIT_SUCCESS;                                                // Exit with success
}
