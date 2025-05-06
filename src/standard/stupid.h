/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#ifndef STD_STUPID_STANDARD
#define STD_STUPID_STANDARD
#pragma once

#include <stdint.h>

// These errors are defined to use in the library, if a value of -1 is given
// it's a catastrophic error which means fundemental flow of program has broken,
// if it's a -2 then it could be the result of reading from a socket that has no
// data, and if it's a -3 it means it's an error that does not need to be
// handeled and is presumed to be normal flow of program.
#define NO_ERROR 0
#define CATASTROPHIC_ERROR -1
#define EXPECTED_ERROR -2
#define IGNORE_ERROR -3

#define STDIN 0
#define STDOUT 1
#define STDERROR 2

#ifndef bool
typedef uint8_t bool;
#define true 1
#define false 0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

/**
 * Obtains the length of a string by looking for the null terminator.
 *
 * Input:
 * - Pointer to a character array
 *
 * Returns:
 * - >=0 Length of the string not including null terminator
 * - -1 if the provided pointer is NULL
 */
int stupid_strlen(const char *string);

/**
 * Takes in a start number and puts it to the power specified
 *
 * Input:
 * - Int of the number to factor
 * - Int of the exponent for the power calculation
 *
 * Returns:
 * - >=0 Returned calculated power value
 * - -1 if an integer overflow occurs
 */
int stupid_power(int start, int exponent);

/**
 * Takes in an integer and returns the absolute value from 0
 *
 * Input:
 * - Int of the number to grab the absolute value of
 *
 * Returns:
 * - >=0 Absolute value from 0 from the input
 * - -1 if an integer overflow occurs
 */
int stupid_abs(int input);

/**
 * Takes in a pointer to a null-terminated character array that contains a
 * number to be parsed
 *
 * Input:
 * - Pointer to a null-terminated character array that represents a number that
 * is <=INT_MAX
 *
 * Returns:
 * - > 0 < Number that was parsed
 * - 0 Number was equal to 0 or no number was parsed
 */
int stupid_char_int(char *input);

/**
 * Takes a character buffer and an integer and converts the integer to it's
 * character representation.
 *
 * Input:
 * - Pointer to a character buffer
 * - Int with the length of the character buffer
 * - Int of the value that should be converted
 *
 * Returns:
 * - 0 Integer was successfully converted
 * - -1 Pointer was NULL or length of buffer was less than (-)digits+1
 */
int stupid_int_char(char *buffer, int len, int src);

/**
 * Takes in a pointer to a null terminated character array, and converts all
 * letters to lowercase
 *
 * Input:
 * - Pointer to a null terminated character array
 *
 * Returns:
 * - 0 Integer was successfully converted
 * - -1 Pointer was NULL
 */
int stupid_str_lowercase(char *buffer);

/**
 * Takes in a pointer to a null terminated character array, and converts all
 * letters to uppercase
 *
 * Input:
 * - Pointer to a null terminated character array
 *
 * Returns:
 * - 0 Integer was successfully converted
 * - -1 Pointer was NULL
 */
int stupid_str_uppercase(char *buffer);

/**
 * Takes in 2 pointers to null terminated character arrays and compares them to
 * see if they are the same.
 *
 * Input:
 * - Pointer to a null terminated character array
 * - Pointer to a null terminated character array
 *
 * Returns:
 * - 0 Contents of arrays match
 * - -1 Pointer was NULL
 * - -2 Contents of array did not match
 */
int stupid_strcmp(char *buffer, char *compare);

/**
 * Takes in a pointer to a null terminated character and copies from the
 * it to the destination buffer
 *
 * Input:
 * - Pointer to the destination buffer
 * - Pointer to a null-terminated character array as the source buffer
 *
 * Returns:
 * - 0 Copy was successful
 * - -1 Pointer was NULL
 */
int stupid_strcpy(char *buffer, char *src);

/**
 * Takes in a pointer to a null terminated character and copies from the
 * it to the destination buffer, with the amount of bytes being copied being set
 * with size, and adding a null terminator at the end.
 *
 * Input:
 * - Pointer to the destination buffer
 * - Pointer to a character array with a length of < size
 * - Int that is the amount of characters to be copied
 *
 * Returns:
 * - 0 Copy was successful
 * - -1 Pointer was NULL
 */
int stupid_strncpy(char *buffer, char *src, int size);

/**
 * Takes in a sum of a set of values, and an amount of elements that where
 * summed up.
 *
 * Input:
 * - Float of a sum of the values
 * - Int of the amount of elements that where summed
 * Returns:
 * - Float value of the calculated average
 */
float stupid_average(float sum, int count);

/**
 * Takes in 2 null-terminated character arrays, and will look for the second
 * character array in the first to find a sub string
 *
 * Input:
 * - Pointer to a null-terminated character array that is searched through
 * - Pointer to a null-terminated character array that is looked for in the
 * first Returns:
 * - 0 <= Index where the sub string starts
 * - -1 Pointer was NULL
 * - -2 Sub string was not found inside of string
 */
int stupid_find_substring(char *string, char *substring);

/**
 * Takes in a character array, and an array of bytes, it then converts these
 * bytes into there hexadecimal representation and puts them into the character
 * buffer with a null-terminator at the end
 *
 * Input:
 * - Pointer to a character array that at least has a size of 2*(Bytes)+1
 * - Int with the size of the buffer to be copied into
 * - Pointer to an array of bytes
 * - Int with the amount of bytes that should be converted from the input
 * first
 * Returns:
 * - 0 Conversion was successful
 * - -1 Pointer was NULL or size of output buffer is too small
 */
int stupid_bytes_to_hex(char *buffer, unsigned int outssz, uint8_t *input,
                        unsigned int insz);

#endif /* ifndef STD_STUPID_STANDARD */
