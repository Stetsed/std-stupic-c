/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#ifndef STD_STUPID_STANDARD
#define STD_STUPID_STANDARD
#pragma once

#include <stdint.h>
#include <unistd.h>

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

#ifdef DEBUG
#define SHOW printf
#else
#define SHOW // macros
#endif

// Takes in a null delimited string and returns the length of the string
// null-indexed.
int stupid_strlen(const char *string);

// Convert a null delimited string to either all uppercase charachters or lower
// case charachters.
void stupid_str_lowercase(char *buffer);
void stupid_str_uppercase(char *buffer);

// Methods to print to the standard STDOUT(1), can use println to include adding
// the line return.
void stupid_print(const char *output);
void stupid_println(const char *output);

int stupid_power(int start, int factor);

int stupid_buffer_read(char *buff, int bytes);
// Input: char[] that contains a number to be parsed, number cannot be >=
// INT_MAX
int stupid_char_int(char *input);
// Input: char[] that contains a number to be parsed, number cannot be >=
// INT_MAX, compared to stupid_char_int it will return -1 if not a valid number
// instead of 0
int stupid_char_int_error(char *input);
// Buffer: char[] that has a size of digits + 2
// Input: Int that is converted to a string
void stupid_int_char(char *buffer, int input);
// Compares 2 strings, returns EXPECTED_ERROR if they don't, otherwise returns 0
int stupid_strcmp(char *string, char *string2);
// Compares 2 strings, returns EXPECTED_ERROR if they don't, otherwise returns
// 0. Accepts another argument which is a string for the charachters to ignore
// inside of the string.
int stupid_strcmp_ignorec(char *string, char *string2, char *chartoign);

// Function takes in a value from ERRNO, and returns the error printed out,
// and exits the program.
void stupid_handle_errno(int error);

// Function that takes in a maximum and a minimum, and returns a random number
// between these 2 using system RAND.
int stupid_random(int maximum, int minimum);

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
int stupid_bytes_to_hex(char *output, size_t outssz, uint8_t *input,
                        size_t insz);

#endif /* ifndef STD_STUPID_STANDARD */
