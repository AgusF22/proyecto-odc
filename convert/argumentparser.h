#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

extern int* helpArgPresent;
extern int* viewArgPresent;

extern char* numberArgIntegerValue;
extern char* numberArgFractionValue;
extern int* sourceArgValue;
extern int* destArgValue;

extern void freeAll();

/**
* @brief Converts the given character to upper case.
* @brief A pointer to the character to convert.
*/
void toUpperCase(char* character);

/**
* @brief Stores the identifier character for the given string in the given pointer.
* @details The identifier character is the second character of the argument, for the arguments of the form "-x", where x is any character.
* @param str A string, the argument to check. Valid arguments are "-n", "-s", "-d", "-h", and "-v".
* @param output A pointer to char, where the output will be stored. If the input argument is not valid, the output is a null character.
*/
void argToChar(char* str, char* output);

/**
* @brief Checks if the given character is a valid digit for a given base.
* @param digit A pointer to char, the character to check.
* @param base A pointer to integer, pointing to a value in the range [2, 16], the base to check.
* @param control A pointer to integer. This procedure will store EXIT_FAILURE on it if an error occurred.
* @attention Calling this procedure with base outside range [2, 16] is undefined behavior.
*/
void validateDigit(const char* digit, const int* base, int* control);

/**
* @brief Checks if the given array is a valid number in the current source base argument value.
* @param toParseNArg The array to check.
* @param control A pointer to integer. This procedure will store EXIT_FAILURE on it if an error occurred.
*/
void parseN(char* toParseNArg, int* control);

/**
* @brief Checks if a given base is valid, and, if it is, stores it in the given pointer.
* @param base A pointer to integer, the base to check.
* @param baseArg A pointer to integer, pointing to the memory address in which, in case of being valid, the base will be stored.
* @param control A pointer to integer. This procedure will store EXIT_FAILURE on it if an error occurred.
*/
void parseBase(const int* base, int* baseArg, int* control);

/**
* @brief Checks if the given arguments are valid for the program.
* @param argc The number of arguments.
* @param argv An array of strings, the arguments for the program execution.
*/
void parseArguments(int* argc, char* argv[]);

#endif // ARGUMENTPARSER_H
