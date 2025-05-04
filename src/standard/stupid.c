/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

// Header
#include "stupid.h"
//

int stupid_strlen(const char *string) {
  if (string == NULL) {
    return -1;
  }
  int counter = 0;
  for (; string[counter]; counter++)
    ;
  return counter;
}

int stupid_power(int start, int factor) {
  int counter = 0;
  int returning = start;
  int before = 0;
  if (factor == 0) {
    return 1;
  }
  while (counter < factor - 1) {
    before = returning;
    returning *= start;
    if (returning < before) {
      return -1;
    }
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

int stupid_char_int(char *input) {
  int returning = 0;
  bool first = true;
  bool negative = false;

  while ((*input >= '0' && *input <= '9') || (first == true && *input == '-')) {
    first = false;
    returning *= 10;
    if (*input == '-') {
      negative = true;
    } else {
      returning += (*input - '0');
    }
    input++;
  }
  if (negative) {
    returning *= -1;
  }

  return returning;
}

int stupid_int_char(char *buffer, int len, int src) {
  if (buffer == NULL) {
    return -1;
  }
  bool negative = false;
  int digits = 1;
  if (src < 0) {
    *buffer = '-';
    buffer++;
    src = stupid_abs(src);
    negative = true;
  }
  for (int i = 10; true; i *= 10) {
    if (src / i > 0) {
      digits++;
      continue;
    } else {
      break;
    }
  }
  if (len < (digits + 1 + negative)) {
    return CATASTROPHIC_ERROR;
  }

  for (int i = 0; i < digits; i++) {
    char charachter_gotten = (src / stupid_power(10, digits - i - 1)) + '0';
    buffer[i] = charachter_gotten;
    src %= stupid_power(10, digits - i - 1);
  }

  buffer[digits + 1] = 0;
  return 0;
}

int stupid_str_lowercase(char *buffer) {
  if (buffer == NULL) {
    return -1;
  }
  int i = 0;
  for (; buffer[i]; i++) {
    if (buffer[i] > 64 && buffer[i] < 91) {
      buffer[i] += 32;
    }
  }
  return 0;
}

int stupid_str_uppercase(char *buffer) {
  if (buffer == NULL) {
    return -1;
  }
  int i = 0;
  for (; buffer[i]; i++) {
    if (buffer[i] > 96 && buffer[i] < 123) {
      buffer[i] -= 32;
    }
  }
  return 0;
}

int stupid_strcmp(char *buffer, char *compare) {
  if (buffer == NULL || compare == NULL) {
    return -1;
  }
  int buffer_length = stupid_strlen(buffer);
  int compare_length = stupid_strlen(compare);

  if (buffer_length != compare_length) {
    return -2;
  } else {
    for (int i = 0; i < buffer_length; i++) {
      if (buffer[i] != compare[i]) {
        return -2;
      }
    }
  }
  return 0;
}

int stupid_strcpy(char *buffer, char *input) {
  if (buffer == NULL || input == NULL) {
    return -1;
  }
  int i = 0;
  for (; input[i]; i++) {
    buffer[i] = input[i];
  }

  buffer[i + 1] = 0;
  return 0;
}

int stupid_strncpy(char *buffer, char *input, int size) {
  if (buffer == NULL || input == NULL) {
    return -1;
  }
  int i = 0;
  for (; input[i] && i < size; i++) {
    buffer[i] = input[i];
  }

  buffer[i + 1] = 0;
  return 0;
}

float stupid_average(float sum, int count) {
  float average = (float)sum / (float)(count);
  return average;
}

int stupid_find_substring(char *string, char *substring) {
  if (string == NULL || substring == NULL) {
    return -1;
  }
  int string_length = stupid_strlen(string);
  int substring_length = stupid_strlen(substring);

  if (!string_length || !substring_length) {
    return -2;
  }
  for (int i = 0; i <= string_length - substring_length; i++) {
    int matches = 0;
    if (string[i] == substring[0]) {
      matches++;
      for (int b = 1; b <= substring_length; b++) {
        if (string[i + b] == substring[b]) {
          matches++;
        }
        if (matches == substring_length) {
          return i;
        }
      }
    }
  }
  return -2;
}

int stupid_bytes_to_hex(char *output, unsigned int outssz, uint8_t *input,
                        unsigned int insz) {
  if (output == NULL || input == NULL || (insz * 2 + 1 > outssz)) {
    return -1;
  }
  const char hex[] = "0123456789abcdef";
  char *poutput = output;
  uint8_t *pinput = input;

  for (; pinput < input + insz; poutput += 2, pinput++) {
    poutput[0] = hex[(*pinput >> 4) & 0xF];
    poutput[1] = hex[*pinput & 0xF];
  }
  poutput[0] = 0;

  return 0;
}
