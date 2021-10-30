#ifndef BASECONVERTER_H
#define BASECONVERTER_H

#include<math.h>

/**
* @brief Stores the character that represents the given value in the output pointer.
* @param num A pointer to an integer number between 0 and 15.
* @param output A pointer to a char. This is where the output is stored.
* @warning An invalid num entry will cause the output pointer to become NULL.
*/
void digitChar(const int* num, char* output);

/**
* @brief Stores the value of the given character in the output pointer.
* @details The stored value is value of the character when used to represent numbers in different bases
* (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F; for 0 to 15 respectively).
* @param num A pointer to a char between 0 and 9 or between A and F.
* @param output A pointer to an integer. This is where the output character is stored.
* @warning An invalid num entry will cause the output pointer to become NULL.
*/
void digitValue(const char* num, int* output);

/**
* @brief Verifies if the given number in base 10 is representable in the given base with a precision of 10.
* @param num A pointer to a 64-bit integer, the number to check.
* @param baseDest A pointer to an integer, the base to check.
* @return A pointer, pointing to 1 if the number is representable in the given base.
* @return A pointer, pointing to 0 if the number is not representable in the given base.
* @note The returned pointer is allocated dynamically.
*/
int* isRepresentable(const long long* num, const int* baseDest);

/**
* @brief Calculates a base change using the integer multiplication method.
* @details Multiplication method for integers is used to change base operating in the destination base, so it's used to change from any base to base 10.
* @param nInteger An array of char, representing a number coded in a base from 2 to 16.
* @param sourceBase A pointer to integer, with value from 2 to 16, representing the base of the input number.
* @param viewArgument A pointer to integer, with value 1 or 0, depending on if the intermediate calculations need to be shown on the console.
* @return A pointer to a 64-bit integer, the input number converted to base 10.
* @note The returned pointer is allocated dynamically.
*/
long long* integerMultiplicationMethod(const char* nInteger, const int* sourceBase, const int* viewArgument);

/**
* @brief Calculates a base change using the integer division method.
* @details Division method for integers is used to change base operating in the source base, so it's used to change from base 10 to any base.
* @param nInteger A pointer to a 64-bit integer, the base 10 number to convert.
* @param destBase A pointer to integer, with value from 2 to 16, representing the destination base for the conversion.
* @param viewArgument A pointer to integer, with value 1 or 0, depending on if the intermediate calculations need to be shown on the console.
* @return An array of characters, the input number converted to the given base.
* @note The returned pointer is allocated dynamically.
*/
char* integerDivisionMethod(long long* nInteger, const int* destBase, const int* viewArgument);

/**
* @brief Calculates a base change using the fractional division method.
* @details Division method for fractional numbers is used to change base operating in the destination base, so it's used to change from any base to base 10.
* @param nFraction An array of char, representing a number coded in a base from 2 to 16.
* @param sourceBase A pointer to integer, with value from 2 to 16, representing the base of the input number.
* @param viewArgument A pointer to integer, with value 1 or 0, depending on if the intermediate calculations need to be shown on the console.
* @return A pointer to a floating-point number, the input number converted to base 10.
* @note The returned pointer is allocated dynamically.
*/
float* fractionDivisionMethod(const char* nFraction, const int* sourceBase, const int* viewArgument);

/**
* @brief Calculates a base change using the fractional multiplication method.
* @details Multiplication method for fractional numbers is used to change base operating in the source base, so it's used to change from base 10 to any base.
* @param nFraction A pointer to a floating-point number, the number to convert.
* @param destBase A pointer to integer, with value from 2 to 16, representing the destination base for the conversion.
* @param viewArgument A pointer to integer, with value 1 or 0, depending on if the intermediate calculations need to be shown on the console.
* @return  An array of characters, the input number converted to the given base.
* @note The returned pointer is allocated dynamically.
* @attention The value stored in the address pointed by nFraction is consumed by this function.
*/
char* fractionMultiplicationMethod(float* nFraction, const int* destBase, const int* viewArgument);

#endif // BASECONVERTER_H
