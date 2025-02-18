/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

// #include "stupid.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int stupid_strlen(const char *string) {
  int counter = 0;
  for (; string[counter]; counter++)
    ;
  return counter;
}

int stupid_power(int start, int factor) {
  int counter = 0;
  int returning = start;
  if (factor == 0) {
    return 1;
  }
  while (counter < factor - 1) {
    returning *= start;
    counter++;
  }
  return returning;
}

int stupid_abs(int input) {
  if (input < 0) {
    return 0 - input;
  }
  return input;
}

void stupid_print(const char *output) {
  write(fileno(stdout), output, stupid_strlen(output));
}

void stupid_println(const char *output) {
  write(fileno(stdout), output, stupid_strlen(output));
  write(fileno(stdout), "\n", 1);
}

int stupid_buffer_read(char *buff, int bytes) {
  int status = read(fileno(stdin), buff, bytes);
  buff[status] = 0;
  if (status > 0) {
    return status;
  } else {
    return -1;
  }
}

// Assumes that byte is a number between 0 and 9, otherwise returns -1 for error
int stupid_char_int(char *input) {
  int multiplier = 1;
  int returning = 0;
  int length = stupid_strlen(input);
  input += length - 1;
  bool first = true;

  while (*input >= '0' && *input <= '9' || first == true && *input == '\n') {

    if (*input == '\n') {
      first = false;
    } else {
      int returning_add = (*input - '0') * multiplier;
      returning += returning_add++;
      multiplier *= 10;
    }
    --input;
  }

  return returning;
}

void stupid_int_char(char *buffer, int input) {
  int digits = 1;
  if (input < 0) {
    *buffer = '-';
    buffer++;
    input = stupid_abs(input);
  }
  for (int i = 10; true; i *= 10) {
    if (input / i > 0) {
      digits++;
      continue;
    } else {
      break;
    }
  }

  for (int i = 0; digits > i; i++) {
    char charachter_gotten = (input / stupid_power(10, digits - i - 1)) + '0';
    buffer[i] = charachter_gotten;
    input %= stupid_power(10, digits - i - 1);
  }

  buffer[digits + 1] = 0;
}

void stupid_strcpy(char *buffer, char *input) {
  int i = 0;
  for (; input[i]; i++) {
    buffer[i] = input[i];
  }

  buffer[i + 1] = 0;
}

int stupid_totally_safe_strcpy(char *buffer, int bufflen, char *input) {
  int i = 0;
  for (; input[i]; i++) {
    if (i >= bufflen) {
      return -1;
    }
    buffer[i] = input[i];
  }

  buffer[i + 1] = 0;
  return 0;
}

void stupid_str_lowercase(char *buffer) {
  int i = 0;
  for (; buffer[i]; i++) {
    if (buffer[i] > 64 && buffer[i] < 91) {
      buffer[i] += 32;
    }
  }
  buffer[i + 1] = 0;
}

void stupid_str_uppercase(char *buffer) {
  int i = 0;
  for (; buffer[i]; i++) {
    if (buffer[i] > 96 && buffer[i] < 123) {
      buffer[i] -= 32;
    }
  }
  buffer[i + 1] = 0;
}

void stupid_handle_errno(int error) {
  char *errorio = strerror(error);
  stupid_println(errorio);
  exit(1);
}

float stupid_average(float sum, int count) {
  float average = (float)sum / (float)(count);
  return average;
}

int stupid_random(int maximum, int minimum) {
  srand(time(NULL));
  return (rand() % (maximum + 1 - minimum) + minimum);
}
