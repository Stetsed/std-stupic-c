#if defined(unix) || defined(__unix__) || defined(__unix)
/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */
#ifndef STD_STUPID_UNIX
#define STD_STUPID_UNIX
#pragma once

#include <standard/stupid.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Takes in a pointer to a null-terminated character array and prints this to
 * STDOUT(1)
 *
 * Input:
 * - Pointer to a charachter array
 *
 * Returns:
 * - 0 String was correctly printed
 * - -1 if pointer was NULL
 */
int stupid_print(const char *output);

/**
 * Takes in a pointer to a null-terminated character array and prints this to
 * STDOUT(1) and a line return
 *
 * Input:
 * - Pointer to a character array
 *
 * Returns:
 * - 0 String was correctly printed
 * - -1 if pointer was NULL
 */
int stupid_println(const char *output);

/**
 * Takes in a pointer to a byte array, and an amount of bytes to read from
 * STDIN(0)
 *
 * Input:
 * - Pointer to a byte array to store data in
 * - Int of the amount of bytes to read, not > size buffer
 *
 * Returns:
 * - >=0 Amount of bytes read into buffer
 * - -1 Pointer to buffer was NULL or Error occurred while reading
 */
int stupid_buffer_read(uint8_t *buff, int bytes);

/**
 * Takes in an upper bound and a lower bound and generates a random number, rand
 * source should be set before calling with srand(time(NULL))
 *
 * Input:
 * - Int of the maximum number the random should return
 * - Int of the minimum number the random should return
 *
 * Returns:
 * - Maximum > Return > Minimum Integer is returned
 */
int stupid_random(int maximum, int minimum);

#endif /* ifndef STD_STUPID_UNIX */

#endif /* Check if platform is unix */
