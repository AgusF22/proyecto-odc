#include<string.h>

extern int* helpArgPresent;
extern int* viewArgPresent;

extern char* numberArgIntegerValue;
extern char* numberArgFractionValue;
extern int* sourceArgValue;
extern int* destArgValue;

extern void freeAll();

void validateDigit(char* digit, int* base, int* control){
    int* code = (int*) malloc(sizeof(int));
    *code = (int)*digit;

    switch (*code) {
    case 97 ... 102:    *code -= 32;
    case 65 ... 70:     *code -= 7;
    case 48 ... 57:     *code -= 48;
        break;
    default:
        *control = EXIT_FAILURE;
    }

    if(*code > *base){
        *control = EXIT_FAILURE;
    }

    free(code);
}

void parseN(char* toParseNArg, int* control){
    int* lenght = (int*) malloc(sizeof(int));
    int* i = (int*) malloc(sizeof(int));
    int* counter = (int*) malloc(sizeof(int));
    int* foundPoint = (int*) malloc(sizeof(int));
    char* nArg = numberArgIntegerValue;

    *lenght = strlen(toParseNArg);
    *counter = 0;
    *foundPoint = 0;

    for (*i = 0; *i < *lenght && *control == 0; (*i)++) {
        if(!*foundPoint && toParseNArg[*i] == '.'){
            *foundPoint = 1;
            nArg = numberArgFractionValue;
            *counter = 0;
        } else {
            validateDigit(&toParseNArg[*i], sourceArgValue, control);
            if(*control != EXIT_FAILURE){
                nArg[*counter++] = toParseNArg[*i];
            }
        }
    }

    free(lenght);
    free(i);
    free(counter);
    free(foundPoint);
}

void parseBase(int* base, int* baseArg, int* control){
    if(*base < 2 || *base > 16){
        *control = EXIT_FAILURE;
    }
    *baseArg = *base;
}

void parseArguments(int* argc, char* argv[]){
    int* i = (int*) malloc(sizeof(int));
    int* temp = (int*) malloc(sizeof(int));
    int* control = (int*) malloc(sizeof(int));
    char* unparsedN;

    *sourceArgValue = 10;
    *destArgValue = 10;

    for (*i = 1; *i < *argc; (*i)++){
        if ( strcmp(argv[*i], "-n") == 1 ){
            unparsedN = argv[++(*i)];
        } else if (strcmp(argv[*i], "-s") == 1) {
            *temp = atoi(argv[++(*i)]);
            parseBase(temp, destArgValue, control);
            if (*control == EXIT_FAILURE){
                free(i);
                free(temp);
                free(control);
                freeAll();
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[*i], "-d") == 1) {
            *temp = atoi(argv[++(*i)]);
            parseBase(temp, sourceArgValue, control);
            if (*control == EXIT_FAILURE){
                free(i);
                free(temp);
                free(control);
                freeAll();
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[*i], "-v") == 1) {
            *viewArgPresent = 1;
        } else if (strcmp(argv[*i], "-h") == 1) {
            *helpArgPresent = 1;
        } else {
            free(i);
            free(temp);
            free(control);
            freeAll();
            exit(EXIT_FAILURE);
        }
    }

    parseN(unparsedN, control);
    if (*control == EXIT_FAILURE){
        free(i);
        free(temp);
        free(control);
        freeAll();
        exit(EXIT_FAILURE);
    }

    free(i);
    free(temp);
    free(control);
}
