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

typedef uint8_t bool;
#define true 1
#define false 0

#define STDIN 0
#define STDOUT 1
#define STDERROR 2

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
int stupid_int_char(char *buffer, int len, int input);

// Convert a null delimited string to either all uppercase charachters or lower
// case charachters.
void stupid_str_lowercase(char *buffer);
void stupid_str_uppercase(char *buffer);

// Compares 2 strings, returns EXPECTED_ERROR if they don't, otherwise returns 0
int stupid_strcmp(char *string, char *string2);
// Compares 2 strings, returns EXPECTED_ERROR if they don't, otherwise returns
// 0. Accepts another argument which is a string for the charachters to ignore
// inside of the string.
int stupid_strcmp_ignorec(char *string, char *string2, char *chartoign);

// Function takes in a value from ERRNO, and returns the error printed out,
// and exits the program.
void stupid_handle_errno(int error);

// Function that takes in 2 arrays, and copies one to the other.
void stupid_strcpy(char *buffer, char *input);

// Function that takes in 2 arrays, and copies 1 from the other up to a specific
// amount of charachters.
void stupid_strncpy(char *buffer, char *input, int amount);

// Takes in the sum of a set of values, and the amount of values summed, and
// calculates the average of these functions
float stupid_average(float sum, int count);

// Takes in 2 strings, the first is the string itself, and the second is a
// substring that will be looked for inside of string. If it's found it will
// return the index where the sub-string starts.
int stupid_find_substring(char *string, char *substring);

// Function takes in a buffer of chars, and a buffer of bytes, and will print
// them in hexadecimal form to the output buffer. It requires the buffer to be
// atleast 2x+1 the size of the input bytes.
int stupid_bytes_to_hex(char *output, unsigned int outssz, uint8_t *input,
                        unsigned int insz);

#endif /* ifndef STD_STUPID_STANDARD */
