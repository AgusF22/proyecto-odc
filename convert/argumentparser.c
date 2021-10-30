#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int* helpArgPresent;
extern int* viewArgPresent;

extern char* numberArgIntegerValue;
extern char* numberArgFractionValue;
extern int* sourceArgValue;
extern int* destArgValue;

extern void freeAll();

void toUpperCase(char* character){
    if (*character >= 97 && *character <= 122){
        *character = *character - 32;
    }
}

void argToChar(char* str, char* output){
    if (str[0] == '-' && str[2] == '\0') {              // If first character is '-' and third character is the termination character
        switch (str[1]) {                                   // check second character
        case 'n':   *output = 'n';  break;
        case 's':   *output = 's';  break;
        case 'd':   *output = 'd';  break;
        case 'h':   *output = 'h';  break;
        case 'v':   *output = 'v';  break;
        default:    *output = '\0'; break;                  // if second character is invalid, output is null character
        }
    } else {                                            // else output is null character
        *output = '\0';
    }
}

void validateDigit(const char* digit, const int* base, int* control){
    int* code;                                         // The digit's ASCII code
    code = (int*) malloc(sizeof(int));                 // Allocate dynamic memory
    *code = (int)*digit;

    /*
    *   This switch block converts the ASCII code of a digit to a number n between 0 and 16 so that n is lower than the bases that use it.
    */
    switch (*code) {
    case 97 ... 102:    *code -= 32;                    // If code is between 97 and 102 means digit is between 'A' and 'F', so subtract 32 to make it equal to 'a' to 'f' codes
    case 65 ... 70:     *code -= 7;                     // If code is between 65 and 70 means digit is between 'a' and 'f', so subtract 7 to make it start after the 0 to 9 codes
    case 48 ... 57:     *code -= 48;                    // If code is between 48 and 57 means digit is between 0 and 9, so subtract 48 to make it start from 0
        break;
    default:
        *control = EXIT_FAILURE;                        // If code is not in any case, means digit is not in 0 to 9 or a/A to f/F range
    }

    if(*code >= *base){                                  // If converted ASCII code is higher than base, means the digit is not used in the base
        *control = EXIT_FAILURE;                            // So, inform failure
    }

    free(code);
}

void parseN(char* toParseNArg, int* control){

    int* length;                                                        // Variable for the length of the string to parse
    int* i;                                                             // index for loops
    int* counter;                                                       // counter for array writing
    int* foundPoint;                                                    // condition for fraction point found
    char* nArg;                                                         // n argument value storage pointer (to separate integer and fraction parts)

    length = (int*) malloc(sizeof(int));                                // ***********************
    i = (int*) malloc(sizeof(int));                                     // ***********************
    counter = (int*) malloc(sizeof(int));                               // Allocate dynamic memory
    foundPoint = (int*) malloc(sizeof(int));                            // ***********************
    nArg = numberArgIntegerValue;                                       // ***********************

    *length = 0;                                                        // Start with length equal 0
    while(toParseNArg[*length] != '\0'){                                // Traverse string until null character
        (*length)++;                                                    // For each non null character, increment the length by one
    }
    *counter = 0;                                                       // Initialize counter as 0
    *foundPoint = 0;                                                    // Initialize foundPoint as false

    for (*i = 0; *i < *length && *control != EXIT_FAILURE; (*i)++) {    // Traverse all characters or until error
        toUpperCase(&toParseNArg[*i]);
        if(!*foundPoint && toParseNArg[*i] == '.'){                     // If point found
            *foundPoint = 1;                                                // Set foundPoint to true
            nArg = numberArgFractionValue;                                  // Change n value storage from integer to fraction
            *counter = 0;                                                   // Set counter to 0, to begin storing the fraction part from 0
        } else {                                                        // If the character is not a point or the point was already found
            validateDigit(&toParseNArg[*i], sourceArgValue, control);       // Validate character with the source base
            if(*control != EXIT_FAILURE){                                   // If there was no error
                nArg[(*counter)++] = toParseNArg[*i];                           // Store character
                nArg[(*counter)] = '\0';                                    // Add null character at the end of the string
            }
        }
    }

    if (numberArgFractionValue[0] == '\0'){                             // If fraction part of n is empty
        for (*i = 0; *i < 5; (*i)++){                                       // fill with 5 zeros
            numberArgFractionValue[*i] = '0';
        }
        numberArgFractionValue[*i] = '\0';                                  // add termination character
    }

    if (strlen(numberArgIntegerValue) > 10 ||
        strlen(numberArgFractionValue) > 5){                            // If integer or fractional part exceeds limits
        *control = EXIT_FAILURE;                                            // set control to error
    }

    free(length);                                                       // *******************
    free(i);                                                            // free dynamic memory
    free(counter);                                                      // *******************
    free(foundPoint);                                                   // *******************
}

void parseBase(const int* base, int* baseArg, int* control){

    if(*base < 2 || *base > 16){            // Valid bases are in the range [2, 16], so if outside that range
        *control = EXIT_FAILURE;                // Inform failure
    }
    *baseArg = *base;                       // Set parameter base value (evaluated base) as base argument value (source or destination)

}

void parseArguments(int* argc, char* argv[]){
    int* i;                                                             // Index for loops
    int* temp;                                                          // Variable to store base string to int conversion
    int* control;                                                       // Error control variable
    char* unparsedN;                                                    // -n argument value variable
    char* argChar;                                                      // An identifier character for argument comparison

    i = (int*) malloc(sizeof(int));                                     // ***********************
    temp = (int*) malloc(sizeof(int));                                  // Allocate dynamic memory
    control = (int*) malloc(sizeof(int));                               // ***********************
    argChar = (char*) malloc(sizeof(char));                             // ***********************
    unparsedN = NULL;                                                   // Starts with null

    numberArgIntegerValue[0] = '\0';                                    // by default, n integer part is empty
    numberArgFractionValue[0] = '\0';                                   // by default, n fractional part is empty
    *sourceArgValue = 10;                                               // By default, source base is 10
    *destArgValue = 10;                                                 // By default, destination base is 10
    *helpArgPresent = 0;                                                // By default, help argument is not present
    *viewArgPresent = 0;                                                // By default, view argument is not present

    for (*i = 1; *i < *argc && *control != EXIT_FAILURE; (*i)++) {       // Traverse all arguments or until error
        argToChar(argv[*i], argChar);

        switch (*argChar) {
        case 'n':                                                       // Parse -n argument
            if (++(*i) < *argc) {                                       // If there is a next argument
                unparsedN = argv[*i];                                       // Parse next argument as -n value
            }
            break;
        case 's':                                                       // Parse -s argument
            if (++(*i) < *argc) {                                       // If there is a next argument
                *temp = atoi(argv[*i]);
                parseBase(temp, sourceArgValue, control);                    // Parse next argument as -s value
            } else {                                                   // Else set failure
                *control = EXIT_FAILURE;
            }
            if (*control == EXIT_FAILURE){                              // If there was a failure, exit with failure
                free(i);
                free(temp);
                free(control);
                free(argChar);
                freeAll();
                printf("Syntax error: invalid source base.\n");
                printf("Use \"convert -h\" for help.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'd':                                                       // Parse -d argument
            if (++(*i) < *argc) {                                       // If there is a next argument
                *temp = atoi(argv[*i]);
                parseBase(temp, destArgValue, control);                     // Parse next argument as -d value
            } else {                                                    // Else set failure
                *control = EXIT_FAILURE;
            }
            if (*control == EXIT_FAILURE){                              // If there was a failure, exit with failure
                free(i);
                free(temp);
                free(control);
                free(argChar);
                freeAll();
                printf("Syntax error: invalid destination base.\n");
                printf("Use \"convert -h\" for help.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'v':                                                       // Parse -v argument
            *viewArgPresent = 1;                                            // -v argument exist, so set to 1
            break;
        case 'h':                                                       // Parse -h argument
            *helpArgPresent = 1;                                            // -h argument exist, so set to 1
            break;
        default:                                                        // If argument is invalid, exit with failure
            free(i);
            free(temp);
            free(control);
            free(argChar);
            freeAll();
            printf("Syntax error: invalid argument detected.\n");
            printf("Use \"convert -h\" for help.\n");
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (*helpArgPresent == 0) {
        if (unparsedN != NULL) {
            parseN(unparsedN, control);
        } else {
            free(i);
            free(temp);
            free(control);
            free(argChar);
            freeAll();
            printf("Syntax error: missing number.\n");
            printf("Use \"convert -h\" for help.\n");
            exit(EXIT_FAILURE);
        }
    }
    if (*control == EXIT_FAILURE){
        free(i);
        free(temp);
        free(control);
        free(argChar);
        freeAll();
        printf("Syntax error: invalid number.\n");
        printf("Use \"convert -h\" for help.\n");
        exit(EXIT_FAILURE);
    }

    free(i);
    free(temp);
    free(control);
    free(argChar);
}
