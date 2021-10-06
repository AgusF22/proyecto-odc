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
