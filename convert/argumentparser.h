#define TESTING

#include<string.h>

extern int* helpArgPresent;
extern int* viewArgPresent;

extern char* numberArgIntegerValue;
extern char* numberArgFractionValue;
extern int* sourceArgValue;
extern int* destArgValue;

extern void freeAll();

void validateDigit(char* digit, int* base, int* control){
    #ifdef TESTING
    printf("Start validateDigit\n");
    #endif // TESTING
    int* code = (int*) malloc(sizeof(int));             // The digit's ASCII code
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

    if(*code > *base){                                  // If converted ASCII code is higher than base, means the digit is not used in the base
        *control = EXIT_FAILURE;                            // So, inform failure
    }

    free(code);
    #ifdef TESTING
    printf("End validateDigit\n");
    #endif // TESTING
}

void parseN(char* toParseNArg, int* control){
    #ifdef TESTING
    printf("Start parseN\n");
    #endif // TESTING
    int* length = (int*) malloc(sizeof(int));                           // Variable for the length of the string to parse
    int* i = (int*) malloc(sizeof(int));                                // index for loops
    int* counter = (int*) malloc(sizeof(int));                          // counter for array writing
    int* foundPoint = (int*) malloc(sizeof(int));                       // condition for fraction point found
    char* nArg = numberArgIntegerValue;                                 // n argument value storage pointer (to separate integer and fraction parts)

    *length = strlen(toParseNArg);                                      // Calculate to parse string length
    #ifdef TESTING
    printf("toParseN length = %i\n", *length);
    #endif // TESTING
    *counter = 0;                                                       // Initialize counter as 0
    *foundPoint = 0;                                                    // Initialize foundPoint as false

    for (*i = 0; *i < *length && *control != EXIT_FAILURE; (*i)++) {    // Traverse all characters or until error
        if(!*foundPoint && toParseNArg[*i] == '.'){                     // If point found
            #ifdef TESTING
            printf("found fractional point\n");
            #endif // TESTING
            *foundPoint = 1;                                                // Set foundPoint to true
            nArg = numberArgFractionValue;                                  // Change n value storage from integer to fraction
            *counter = 0;                                                   // Set counter to 0, to begin storing the fraction part from 0
        } else {                                                        // If the character is not a point or the point was already found
            validateDigit(&toParseNArg[*i], sourceArgValue, control);       // Validate character with the source base
            if(*control != EXIT_FAILURE){                                   // If there was no error
                #ifdef TESTING
                printf("Store %c\n", toParseNArg[*i]);
                #endif // TESTING
                nArg[(*counter)++] = toParseNArg[*i];                           // Store character
                nArg[(*counter) + 1] = '\0';                                    // Add null character at the end of the string
            }
        }
    }

    free(length);
    free(i);
    free(counter);
    free(foundPoint);
    #ifdef TESTING
    printf("End parseN\n");
    #endif // TESTING
}

void parseBase(int* base, int* baseArg, int* control){
    #ifdef TESTING
    printf("Start parseBase with base == %d\n", *base);
    #endif // TESTING
    if(*base < 2 || *base > 16){            // Valid bases are in the range [2, 16], so if outside that range
        *control = EXIT_FAILURE;                // Inform failure
    }
    *baseArg = *base;                       // Set parameter base value (evaluated base) as base argument value (source or destination)
    #ifdef TESTING
    printf("End parseBase\n");
    #endif // TESTING
}

void parseArguments(int* argc, char* argv[]){
    #ifdef TESTING
    printf("Start parseArguments\n");
    #endif // TESTING
    int* i = (int*) malloc(sizeof(int));                                // Index for loops
    int* temp = (int*) malloc(sizeof(int));                             // Variable to store base string to int conversion
    int* control = (int*) malloc(sizeof(int));                          // Error control variable
    char* unparsedN = NULL;                                             // -n argument value variable, starts with null

    numberArgIntegerValue[0] = '\0';                                    // by default, n integer part is empty
    numberArgFractionValue[0] = '\0';                                   // by default, n fractional part is empty
    *sourceArgValue = 10;                                               // By default, source base is 10
    *destArgValue = 10;                                                 // By default, destination base is 10
    *helpArgPresent = 0;                                                // By default, help argument is not present
    *viewArgPresent = 0;                                                // By default, view argument is not present

    for (*i = 1; *i < *argc && *control != EXIT_FAILURE; (*i)++) {       // Traverse all arguments or until error
        #ifdef TESTING
        printf("Argument %d == %s\n", *i, argv[*i]);
        #endif // TESTING
        if ( strcmp(argv[*i], "-n") == 0 ){                             // Parse -n argument
            #ifdef TESTING
            printf("Enter -n if block (argument == -n)\n");
            #endif // TESTING
            if (++(*i) < *argc) {                                       // If there is a next argument
                unparsedN = argv[*i];                                       // Parse next argument as -n value
            }
            #ifdef TESTING
            else {
                printf("Missing -n value\n");
            }
            #endif // TESTING
        } else if (strcmp(argv[*i], "-s") == 0) {                       // Parse -s argument
            #ifdef TESTING
            printf("Enter -s if block (argument == -s)\n");
            #endif // TESTING
            if (++(*i) < *argc) {                                       // If there is a next argument
                *temp = atoi(argv[*i]);
                #ifdef TESTING
                printf("atoi(%s) == %d\n", argv[*i], atoi(argv[*i]));
                #endif // TESTING
                parseBase(temp, sourceArgValue, control);                    // Parse next argument as -s value
            } else {                                                   // Else set failure
                #ifdef TESTING
                printf("Missing -s value\n");
                #endif // TESTING
                *control = EXIT_FAILURE;
            }
            if (*control == EXIT_FAILURE){                              // If there was a failure, exit with failure
                free(i);
                free(temp);
                free(control);
                freeAll();
                #ifdef TESTING
                printf("Exit on parseArguments because -s parseBase fails\n");
                #endif // TESTING
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[*i], "-d") == 0) {                       // Parse -d argument
            #ifdef TESTING
            printf("Enter -d if block (argument == -d)\n");
            #endif // TESTING
            if (++(*i) < *argc) {                                       // If there is a next argument
                *temp = atoi(argv[*i]);
                parseBase(temp, destArgValue, control);                     // Parse next argument as -d value
            } else {                                                    // Else set failure
                #ifdef TESTING
                printf("Missing -d value\n");
                #endif // TESTING
                *control = EXIT_FAILURE;
            }
            if (*control == EXIT_FAILURE){                              // If there was a failure, exit with failure
                free(i);
                free(temp);
                free(control);
                freeAll();
                #ifdef TESTING
                printf("Exit on parseArguments because -d parseBase fails\n");
                #endif // TESTING
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[*i], "-v") == 0) {                       // Parse -v argument
            #ifdef TESTING
            printf("Enter -v if block (argument == -v)\n");
            #endif // TESTING
            *viewArgPresent = 1;                                            // -v argument exist, so set to 1
        } else if (strcmp(argv[*i], "-h") == 0) {                       // Parse -h argument
            #ifdef TESTING
            printf("Enter -h if block (argument == -h)\n");
            #endif // TESTING
            *helpArgPresent = 1;                                            // -h argument exist, so set to 1
        } else {                                                        // If argument is invalid, exit with failure
            free(i);
            free(temp);
            free(control);
            freeAll();
            #ifdef TESTING
            printf("Exit on parseArguments because argument is invalid\n");
            #endif // TESTING
            exit(EXIT_FAILURE);
        }
    }

    if (unparsedN != NULL) {
        parseN(unparsedN, control);
    } else {
        *control = EXIT_FAILURE;
    }
    if (*control == EXIT_FAILURE){
        free(i);
        free(temp);
        free(control);
        freeAll();
        #ifdef TESTING
        printf("Exit on parseArguments because parseN fails\n");
        #endif // TESTING
        exit(EXIT_FAILURE);
    }

    free(i);
    free(temp);
    free(control);
    #ifdef TESTING
    printf("Finish parseArguments\n");
    #endif // TESTING
}
