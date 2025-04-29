/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

// Header
#include <stupid.h>
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

void stupid_print(const char *output) {
  write(STDOUT, output, stupid_strlen(output));
}

void stupid_println(const char *output) {
  write(STDOUT, output, stupid_strlen(output));
  write(STDOUT, "\n", 1);
}

int stupid_buffer_read(uint8_t *buff, int bytes) {
  int length = read(STDIN, buff, bytes);
  if (length >= 0) {
    return length;
  } else {
    return -1;
  }
}

// Assumes that byte is a number between 0 and 9
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

void stupid_strncpy(char *buffer, char *input, int amount) {
  int i = 0;
  for (; input[i] && i < amount; i++) {
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

int stupid_strcmp(char *string, char *string2) {
  int string_length = stupid_strlen(string);
  int string2_length = stupid_strlen(string2);

  if (string_length != string2_length) {
    return EXPECTED_ERROR;
  } else {
    for (int i = 0; i < string_length; i++) {
      if (string[i] != string2[i]) {
        return EXPECTED_ERROR;
      }
    }
  }
  return 0;
}

int stupid_strcmp_ignorec(char *string, char *string2, char *chartoign) {
  int string_length = stupid_strlen(string);
  int string2_length = stupid_strlen(string2);
  int chartoign_length = stupid_strlen(chartoign);
  int offset = 0;
  bool done = false;

  for (int i = 0; i < string_length - offset && !done; i++) {
    if (string[i + offset] != string2[i]) {
      bool ignore = false;
      for (int b = 0; b < chartoign_length; b++) {
        if (string[i + offset] == chartoign[b]) {
          ignore = true;
          if (i >= string2_length) {
            done = true;
            break;
          } else {
            i--;
            offset++;
            break;
          }
        }
      }
      if (!ignore) {
        return EXPECTED_ERROR;
      }
    }
  }
  if (offset >= string_length) {
    return EXPECTED_ERROR;
  };
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

float stupid_average(float sum, int count) {
  float average = (float)sum / (float)(count);
  return average;
}

int stupid_random(int maximum, int minimum) {
  return (rand() % (maximum + 1 - minimum) + minimum);
}

int stupid_find_substring(char *string, char *substring) {
  int string_length = stupid_strlen(string);
  int substring_length = stupid_strlen(substring);

  if (!string_length || !substring_length) {
    return -1;
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
  return -1;
}

int stupid_bytes_to_hex(char *output, size_t outssz, uint8_t *input,
                        size_t insz) {
  const char hex[] = "0123456789abcdef";
  char *poutput = output;
  uint8_t *pinput = input;

  if (insz * 2 + 1 > outssz) {
    return CATASTROPHIC_ERROR;
  }

  for (; pinput < input + insz; poutput += 2, pinput++) {
    poutput[0] = hex[(*pinput >> 4) & 0xF];
    poutput[1] = hex[*pinput & 0xF];
  }
  poutput[0] = 0;

  return NO_ERROR;
}
