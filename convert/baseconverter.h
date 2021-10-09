#ifndef BASECONVERTER_H
#define BASECONVERTER_H

#include<math.h>

/**
* @brief Stores the character that represents the given value in the output pointer.
* @param num A pointer to an integer number between 0 and 15.
* @param output A pointer to a char. This is where the output is stored.
* @warning An invalid num entry will cause the output pointer to become NULL.
*/
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

/**
* @brief Stores the value of the given character in the output pointer.
* @details The stored value is value of the character when used to represent numbers in different bases
* (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F; for 0 to 15 respectively).
* @param num A pointer to a char between 0 and 9 or between A and F.
* @param output A pointer to an integer. This is where the output character is stored.
* @warning An invalid num entry will cause the output pointer to become NULL.
*/
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

/**
* @brief Verifies if the given number in base 10 is representable in the given base with a precision of 10.
* @param num A pointer to a 64 bit integer, the number to check.
* @param baseDest A pointer to an integer, the base to check.
* @return A pointer, pointing to 1 if the number is representable in the given base.
* @return A pointer, pointing to 0 if the number is not representable in the given base.
* @note The returned pointer is allocated dynamically.
*/
int* isRepresentable(const long long* num, const int* baseDest) {
    int* toReturn = (int*) malloc(sizeof(int));

    if ( pow(*baseDest, 10) - 1 >= *num)                // If num is lower or equal to the maximum representable number in the given base with 10 precision digits
        *toReturn = 1;                                      // num is representable
    else
        *toReturn = 0;                                      // num is not representable

    return toReturn;
}

/**
* @brief Calculates a base change using the integer multiplication method.
* @details Multiplication method for integers is used to change base operating in the destination base, so it's used to change from any base to base 10.
* @param nInteger An array of char, representing a number coded in a base from 2 to 16.
* @param sourceBase A pointer to integer, with value from 2 to 16, representing the base of the input number.
* @param viewArgument A pointer to integer, with value 1 or 0, depending on if the intermediate calculations need to be shown on the console.
* @return A pointer to a 64 bit integer, the input number converted to base 10.
* @note The returned pointer is allocated dynamically.
*/
long long* integerMultiplicationMethod(const char* nInteger, const int* sourceBase, const int* viewArgument){

    long long* outcome = (long long*)malloc(sizeof(long long));             // Variable to store the outcome of this function
    int* i = (int*) malloc(sizeof(int));                                    // Index for loops
    int* nDigitValue = (int*) malloc(sizeof(int));                          // variable to store a digit from nInteger during nInteger traverse
    int* position = (int*) malloc(sizeof(int));                             // Variable to store a position during nInteger traverse
    long long* prevOutcome = (long long*) malloc(sizeof(long long));        // variable to store the outcome of the previous iteration during calculations
    int* nIntegerLenght = (int*) malloc(sizeof(int));                       // variable to store the length of nInteger

    *outcome = 0;                                                           // By default, outcome is 0
    *nIntegerLenght = 0;                                                    // By default, length is 0

    for (*i = 0; nInteger[*i] != '\0'; (*i)++) {                            // While character in index is not null
        ++(*nIntegerLenght);                                                    // increment length
    }

    if (*viewArgument == 1) {                                               // if viewArgument is true
        printf("Start integer multiplication method\n");                        // inform start of this function calculations
    }

    for (*i = 0; *i < *nIntegerLenght; (*i)++) {                            // Traverse nIntegerCopy, reading all digits
        *prevOutcome = *outcome;                                                // Save outcome to previous outcome

        digitValue(&nInteger[*i], nDigitValue);                                 // Store the value of the digit in the index position of nIntegerCopy
        *position = (*nIntegerLenght - 1) - *i;                                 // Store the position of the digit in the number, that is, counting from right to left
        *outcome += (*nDigitValue) * pow(*sourceBase, *position);               // Multiply the value of the digit, by the base to the power of the digit's position

        if (*viewArgument == 1) {                                               // if viewArgument is true
            printf("%*I64d + (%d * %d^%d) = %I64d\n",                                // print the current iteration status
                   *nIntegerLenght, *prevOutcome, *nDigitValue,
                   *sourceBase, *position, *outcome);
        }
    }

    free(i);                                                                // *******************
    free(nDigitValue);                                                      // *******************
    free(position);                                                         // Free dynamic memory
    free(prevOutcome);                                                      // *******************
    free(nIntegerLenght);                                                   // *******************

    return outcome;
}

/*
 * metodo de la division para enteros (de base 10 a base destBase)
*/
/**
* @brief Calculates a base change using the integer division method.
* @details Division method for integers is used to change base operating in the source base, so it's used to change from base 10 to any base.
* @param nInteger A pointer to a 64 bit integer, the base 10 number to convert.
* @param destBase A pointer to integer, with value from 2 to 16, representing the destination base for the conversion.
* @param viewArgument A pointer to integer, with value 1 or 0, depending on if the intermediate calculations need to be shown on the console.
* @return An array of characters, the input number converted to the given base.
* @note The returned pointer is allocated dynamically.
*/
char* integerDivisionMethod(long long* nInteger, const int* destBase, const int* viewArgument){

    int* representable = (int*) malloc(sizeof(int));                        // Pointer to store the condition of whether the given number is representable or not
    representable = isRepresentable(nInteger, destBase);                    // Verifies if the given number is representable in the given base with a precision of 10
    if(*representable == 0) {                                               // If number is not representable
        free(representable);                                                    //
        free(nInteger);                                                         // Free memory
        freeAll();                                                              // and exit
        exit(EXIT_FAILURE);                                                     //
    }
    free(representable);                                                    // Dispose of representable

    long long* nIntegerCopy = (long long*) malloc(sizeof(long long));       // Pointer to store a copy of nInteger
    char* outcome = (char*) malloc(sizeof(char) * 10);                      // Pointer to store the outcome of this function (as it should be returned)
    char* invertedOutcome = (char*) malloc(sizeof(char) * 10);              // Pointer to store the outcome of this function in inverted order (as the method generates it)
    int* i = (int*) malloc(sizeof(int));                                    // Index for loops
    int* j = (int*) malloc(sizeof(int));                                    // Index for loops
    double* quotient = (double*) malloc(sizeof(double));                    // Pointer to store the quotient of a division
    int* rest = (int*) malloc(sizeof(int));                                 // Pointer to store the remainder of a division
    int* nIntegerLength = (int*) malloc(sizeof(int));                       // Pointer to store the length (digit amount) of nInteger

    *nIntegerLength = 0;                                                    // Initialize length in 0
    *i = 0;                                                                 // Initialize index in 0
    *j = 0;                                                                 // Initialize index in 0
    *nIntegerCopy = *nInteger;                                              // Initialize nIntegerCopy with nInteger value

    while(*nIntegerCopy != 0) {                                             // While nIntegerCopy is not 0
        *nIntegerCopy /= 10;                                                    // divide by ten
        ++(*nIntegerLength);                                                    // increment length (digit amount)
    }

    *nIntegerCopy = *nInteger;                                              // assign nInteger value to nIntegerCopy (because it changed during length calculation)

    if (*viewArgument == 1) {                                               // if viewArgument is true
        printf("Start integer division method\n");                              // inform start of this function calculations
    }

    do {                                                                    // start do
        *quotient = (double) *nIntegerCopy / (double) *destBase;                // Divide nIntegerCopy by the destination base
        *rest = *nIntegerCopy % *destBase;                                      // Get the remainder of the division
        *quotient = trunc(*quotient);                                           // Remove decimal part of the quotient
        digitChar(rest, &invertedOutcome[*i]);                                  // Store the character with value equal to the remainder

        if (*viewArgument == 1)                                                 // if viewArgument is true
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

/**
* @brief Calculates a base change using the fractional division method.
* @details Division method for fractional numbers is used to change base operating in the destination base, so it's used to change from any base to base 10.
* @param nFraction An array of char, representing a number coded in a base from 2 to 16.
* @param sourceBase A pointer to integer, with value from 2 to 16, representing the base of the input number.
* @param viewArgument A pointer to integer, with value 1 or 0, depending on if the intermediate calculations need to be shown on the console.
* @return A pointer to a floating point number, the input number converted to base 10.
* @note The returned pointer is allocated dynamically.
*/
float* fractionDivisionMethod(const char* nFraction, const int* sourceBase, const int* viewArgument) {

    float* outcome = (float*)malloc(sizeof(float));                         // Pointer to store the outcome of this function
    int* i = (int*) malloc(sizeof(int));                                    // Index for loops
    char* digChar = (char*) malloc(sizeof(char));                           // pointer to store a character from nFraction
    int* digValue = (int*) malloc(sizeof(int));                             // pointer to store the value of digChar in base 10
    float* quotient = (float*) malloc(sizeof(float));                       // pointer to store the quotient of a division
    int* length = (int*) malloc(sizeof(int));                               // pointer to store the length of nFraction

    *quotient = 0;                                                          // ***************
    *outcome = 0;                                                           // Initialize in 0
    *length = 0;                                                            // ***************

    for(*i = 0; nFraction[*i] != '\0'; (*i)++){                             // While character in index is not null
        ++(*length);                                                            // increment length
    }

    if (*viewArgument == 1) {                                               // if viewArgument is true
        printf("Start fractional division method\n");                           // inform start of this function calculations
    }

    for (*i = *length - 1; 0 <= *i; (*i)--) {                               // for every character in nFraction (starting from the last position)
        *digChar = nFraction[*i];                                               // Store the character
        digitValue(digChar, digValue);                                          // get the character's value in base 10
        *quotient = (*quotient + *digValue) / *sourceBase;                      // Add the quotient and the character's value, then divide by the source base

        if (*viewArgument == 1) {                                               // if viewArgument is true
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

/**
* @brief Calculates a base change using the fractional multiplication method.
* @details Multiplication method for fractional numbers is used to change base operating in the source base, so it's used to change from base 10 to any base.
* @param nFraction A pointer to a floating point number, the number to convert.
* @param destBase A pointer to integer, with value from 2 to 16, representing the destination base for the conversion.
* @param viewArgument A pointer to integer, with value 1 or 0, depending on if the intermediate calculations need to be shown on the console.
* @return  An array of characters, the input number converted to the given base.
* @note The returned pointer is allocated dynamically.
* @attention The value stored in the address pointed by nFraction is consumed by this function.
*/
char* fractionMultiplicationMethod(float* nFraction, const int* destBase, const int* viewArgument){

    char* outcome = (char*)malloc(sizeof(char) * 5);                        // Pointer to store the outcome of this function
    int* i = (int*) malloc(sizeof(int));                                    // Index for loops
    float* product = (float*) malloc(sizeof(float));                        // Pointer to store a product
    int* truncated = (int*) malloc(sizeof(int));                            // Pointer to store an integer

    if (*viewArgument == 1) {                                               // if viewArgument is true
        printf("Start fractional multiplication method\n");                     // inform start of this function calculations
    }

    for (*i = 0; *i < 5; (*i)++) {                                          // Repeat 5 times, one for each digit to obtain
        *product = (*nFraction) * (*destBase);                                  // Multiply nFraction by the destination base
        *truncated = truncf(*product);                                          // Store the integer part of the product
        digitChar(truncated, &outcome[*i]);                                     // Store the character that represents the value of the integer part in the outcome array

        if (*viewArgument == 1) {                                               // if viewArgument is true
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

#endif // BASECONVERTER_H
