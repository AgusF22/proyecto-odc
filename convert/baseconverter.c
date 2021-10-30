#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern void freeAll();

void digitChar(const int* num, char* output) {
    switch (*num) {
    case 10 ... 15:     *output = *num + 55;        // if value is between 10 and 15, adding 55 matches the value with the ASCII codes from A to F
        break;
    case 0 ... 9:       *output = *num + 48;        // if value is between 0 and 9, adding 48 matches the value with the ASCII codes from 0 (ASCII 48) to 9 (ASCII 57)
        break;
    default:
        output = NULL;                              // if value is invalid, output becomes NULL
    }
}

void digitValue(const char* num, int* output) {
    switch (*num) {
    case 'A' ... 'F':                               // if character is between 'A' and 'F', subtracting 55 to it's ASCII code gives a value of 10 to 15 respectively
        *output = *num - 55;
        break;
    case '0' ... '9':                               // if character is between '0' and '9', subtracting 48 to it's ASCII code gives a value of 0 to 9 respectively
        *output = *num - 48;
        break;
    default:
        output = NULL;                              // if value is invalid, output becomes NULL
    }
}

int* isRepresentable(const long long* num, const int* baseDest) {
    int* toReturn;
    toReturn = (int*) malloc(sizeof(int));

    if (pow(*baseDest, 10) - 1 >= *num)                     // If num is lower or equal to the maximum representable number in the given base with 10 precision digits
        *toReturn = 1;                                          // num is representable
    else
        *toReturn = 0;                                          // num is not representable

    return toReturn;
}

long long* integerMultiplicationMethod(const char* nInteger, const int* sourceBase, const int* viewArgument){

    long long* outcome;                                                     // Variable to store the outcome of this function
    int* i;                                                                 // Index for loops
    int* nDigitValue;                                                       // variable to store a digit from nInteger during nInteger traverse
    int* position;                                                          // Variable to store a position during nInteger traverse
    long long* prevOutcome;                                                 // variable to store the outcome of the previous iteration during calculations
    int* nIntegerLength;                                                    // variable to store the length of nInteger

    outcome = (long long*)malloc(sizeof(long long));                        // ***********************
    i = (int*) malloc(sizeof(int));                                         // ***********************
    nDigitValue = (int*) malloc(sizeof(int));                               // Allocate dynamic memory
    position = (int*) malloc(sizeof(int));                                  // ***********************
    prevOutcome = (long long*) malloc(sizeof(long long));                   // ***********************
    nIntegerLength = (int*) malloc(sizeof(int));                            // ***********************

    *outcome = 0;                                                           // By default, outcome is 0
    *nIntegerLength = 0;                                                    // By default, length is 0

    for (*i = 0; nInteger[*i] != '\0'; (*i)++) {                            // While character in index is not null
        ++(*nIntegerLength);                                                    // increment length
    }

    if (*viewArgument == 1 && *sourceBase != 10) {                          // if viewArgument is true and source base is not 10
        printf("Start integer multiplication method\n");                        // inform start of this function calculations
    }

    for (*i = 0; *i < *nIntegerLength; (*i)++) {                            // Traverse nIntegerCopy, reading all digits
        *prevOutcome = *outcome;                                                // Save outcome to previous outcome

        digitValue(&nInteger[*i], nDigitValue);                                 // Store the value of the digit in the index position of nIntegerCopy
        *position = (*nIntegerLength - 1) - *i;                                 // Store the position of the digit in the number, that is, counting from right to left
        *outcome += (*nDigitValue) * pow(*sourceBase, *position);               // Multiply the value of the digit, by the base to the power of the digit's position

        if (*viewArgument == 1 && *sourceBase != 10) {                      // if viewArgument is true and source base is not 10
            printf("%10I64d + (%2d * %d^%2d) = %I64d\n",                            // print the current iteration status
                   *prevOutcome, *nDigitValue,
                   *sourceBase, *position, *outcome);
        }
    }

    free(i);                                                                // *******************
    free(nDigitValue);                                                      // *******************
    free(position);                                                         // Free dynamic memory
    free(prevOutcome);                                                      // *******************
    free(nIntegerLength);                                                   // *******************

    return outcome;
}

char* integerDivisionMethod(long long* nInteger, const int* destBase, const int* viewArgument){

    int* representable;                                                     // Pointer to store the condition of whether the given number is representable or not
    long long* nIntegerCopy;                                                // Pointer to store a copy of nInteger
    char* outcome;                                                          // Pointer to store the outcome of this function (as it should be returned)
    char* invertedOutcome;                                                  // Pointer to store the outcome of this function in inverted order (as the method generates it)
    int* i;                                                                 // Index for loops
    int* j;                                                                 // Index for loops
    double* quotient;                                                       // Pointer to store the quotient of a division
    int* rest;                                                              // Pointer to store the remainder of a division
    int* nIntegerLength;                                                    // Pointer to store the length (digit amount) of nInteger

    representable = (int*) malloc(sizeof(int));                             // Allocate dynamic memory

    representable = isRepresentable(nInteger, destBase);                    // Verifies if the given number is representable in the given base with a precision of 10

    if(*representable == 0) {                                               // If number is not representable
        printf("Error: input number has more than 10 integer ");
        printf("digits in base %d.\n", *destBase);                              // Inform error
        free(representable);                                                    //
        free(nInteger);                                                         // Free memory
        freeAll();                                                              // and exit
        exit(EXIT_FAILURE);                                                     //
    }
    free(representable);                                                    // Dispose of representable

    nIntegerCopy = (long long*) malloc(sizeof(long long));                  // ***********************
    outcome = (char*) malloc(sizeof(char) * 10);                            // ***********************
    i = (int*) malloc(sizeof(int));                                         // ***********************
    j = (int*) malloc(sizeof(int));                                         // Allocate dynamic memory
    quotient = (double*) malloc(sizeof(double));                            // ***********************
    rest = (int*) malloc(sizeof(int));                                      // ***********************
    nIntegerLength = (int*) malloc(sizeof(int));                            // ***********************
    invertedOutcome = (char*) malloc(sizeof(char) * 10);                    // ***********************

    *nIntegerLength = 0;                                                    // Initialize length in 0
    *i = 0;                                                                 // Initialize index in 0
    *j = 0;                                                                 // Initialize index in 0
    *nIntegerCopy = *nInteger;                                              // Initialize nIntegerCopy with nInteger value

    while(*nIntegerCopy != 0) {                                             // While nIntegerCopy is not 0
        *nIntegerCopy /= 10;                                                    // divide by ten
        ++(*nIntegerLength);                                                    // increment length (digit amount)
    }

    *nIntegerCopy = *nInteger;                                              // assign nInteger value to nIntegerCopy (because it changed during length calculation)

    if (*viewArgument == 1 && *destBase != 10) {                            // if viewArgument is true and destination base is not 10
        printf("Start integer division method\n");                              // inform start of this function calculations
    }

    do {                                                                    // start do
        *quotient = (double) *nIntegerCopy / (double) *destBase;                // Divide nIntegerCopy by the destination base
        *rest = *nIntegerCopy % *destBase;                                      // Get the remainder of the division
        *quotient = trunc(*quotient);                                           // Remove decimal part of the quotient
        digitChar(rest, &invertedOutcome[*i]);                                  // Store the character with value equal to the remainder

        if (*viewArgument == 1 && *destBase != 10)                              // if viewArgument is true and destination base is not 10
            printf("%*I64d / %d = %-*.0lf, remainder = (%2d)10 = (%c)%d\n",         // print the current iteration status
                   *nIntegerLength, *nIntegerCopy, *destBase,
                   *nIntegerLength, *quotient, *rest, invertedOutcome[*i],
                   *destBase);

        *nIntegerCopy = (long long)*quotient;                                   // Replace nIntegerCopy with the quotient of the division
        ++(*i);                                                                 // increment index
    } while (*nIntegerCopy != 0);                                           // repeat if nIntegerCopy is not 0

    invertedOutcome[*i] = '\0';                                             // add termination character to (inverted) outcome string

    while (*i > 0) {                                                        // invert outcome (so it is in the correct order)
        outcome[*j] = invertedOutcome[(*i)-1];
        --(*i);
        ++(*j);
    }
    outcome[*j] = '\0';                                                     // add termination character to outcome string

    free(nIntegerCopy);                                                     // *******************
    free(invertedOutcome);                                                  // *******************
    free(i);                                                                // *******************
    free(j);                                                                // Free dynamic memory
    free(quotient);                                                         // *******************
    free(rest);                                                             // *******************
    free(nIntegerLength);                                                   // *******************

    return outcome;
}

float* fractionDivisionMethod(const char* nFraction, const int* sourceBase, const int* viewArgument) {

    float* outcome;                                                         // Pointer to store the outcome of this function
    int* i;                                                                 // Index for loops
    char* digChar;                                                          // pointer to store a character from nFraction
    int* digValue;                                                          // pointer to store the value of digChar in base 10
    float* quotient;                                                        // pointer to store the quotient of a division
    int* length;                                                            // pointer to store the length of nFraction

    outcome = (float*)malloc(sizeof(float));                                // ***********************
    i = (int*) malloc(sizeof(int));                                         // ***********************
    digChar = (char*) malloc(sizeof(char));                                 // Allocate dynamic memory
    digValue = (int*) malloc(sizeof(int));                                  // ***********************
    quotient = (float*) malloc(sizeof(float));                              // ***********************
    length = (int*) malloc(sizeof(int));                                    // ***********************

    *quotient = 0;                                                          // ***************
    *outcome = 0;                                                           // Initialize in 0
    *length = 0;                                                            // ***************

    for(*i = 0; nFraction[*i] != '\0'; (*i)++){                             // While character in index is not null
        ++(*length);                                                            // increment length
    }

    if (*viewArgument == 1 && *sourceBase != 10) {                          // if viewArgument is true and source base is not 10
        printf("Start fractional division method\n");                           // inform start of this function calculations
    }

    for (*i = *length - 1; 0 <= *i; (*i)--) {                               // for every character in nFraction (starting from the last position)
        *digChar = nFraction[*i];                                               // Store the character
        digitValue(digChar, digValue);                                          // get the character's value in base 10
        *quotient = (*quotient + *digValue) / *sourceBase;                      // Add the quotient and the character's value, then divide by the source base

        if (*viewArgument == 1 && *sourceBase != 10) {                      // if viewArgument is true and source base is not 10
            printf("(%.5f + %d) / 10 = %.5f\n",                                     // print the current iteration status
                   *outcome, *digValue, *quotient);
        }
        *outcome = *quotient;                                                   // store quotient as outcome
    }

    free(i);                                                                // *******************
    free(digChar);                                                          // *******************
    free(digValue);                                                         // Free dynamic memory
    free(quotient);                                                         // *******************
    free(length);                                                           // *******************

    return outcome;
}

char* fractionMultiplicationMethod(float* nFraction, const int* destBase, const int* viewArgument){

    char* outcome;                                                          // Pointer to store the outcome of this function
    int* i;                                                                 // Index for loops
    float* product;                                                         // Pointer to store a product
    int* truncated;                                                         // Pointer to store an integer

    outcome = (char*)malloc(sizeof(char) * 5);                              // ***********************
    i = (int*) malloc(sizeof(int));                                         // Allocate dynamic memory
    product = (float*) malloc(sizeof(float));                               // ***********************
    truncated = (int*) malloc(sizeof(int));                                 // ***********************

    if (*viewArgument == 1 && *destBase != 10) {                            // if viewArgument is true and destination base is not 10
        printf("Start fractional multiplication method\n");                     // inform start of this function calculations
    }

    for (*i = 0; *i < 5; (*i)++) {                                          // Repeat 5 times, one for each digit to obtain
        *product = (*nFraction) * (*destBase);                                  // Multiply nFraction by the destination base
        *truncated = truncf(*product);                                          // Store the integer part of the product
        digitChar(truncated, &outcome[*i]);                                     // Store the character that represents the value of the integer part in the outcome array

        if (*viewArgument == 1 && *destBase != 10) {                        // if viewArgument is true and destination base is not 10
            printf("%.5f * %d = %8.5lf, digit %d^(-%d) = %c\n",                     // print the current iteration status
                   *nFraction, *destBase, *product, *destBase,
                   *i + 1, outcome[*i]);
        }

        *nFraction = *product - truncf(*product);                               // Store in nFraction the fractional part of the product
    }
    outcome[*i] = '\0';                                                     // add termination character to outcome string

    free(i);                                                                // *******************
    free(product);                                                          // Free dynamic memory
    free(truncated);                                                        // *******************

    return outcome;
}
