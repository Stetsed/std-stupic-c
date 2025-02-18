/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#ifndef STD_STUPID_STANDARD
#define STD_STUPID_STANDARD
#pragma once

#include "stupid.c"
#include <stdbool.h>
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
// Buffer: char[] that has a size of digits + 2
// Input: Int that is converted to a string
void stupid_int_char(char *buffer, int input);

// Function takes in a value from ERRNO, and returns the error printed out, and
// exits the program.
void stupid_handle_errno(int error);

#endif /* ifndef STD_STUPID_STANDARD */
