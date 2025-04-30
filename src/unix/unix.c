/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

// Header
#include "unix.h"
//

int stupid_print(const char *output) {
  if (output == NULL) {
    return -1;
  }
  write(STDOUT, output, stupid_strlen(output));
  return 0;
}

int stupid_println(const char *output) {
  if (output == NULL) {
    return -1;
  }
  write(STDOUT, output, stupid_strlen(output));
  write(STDOUT, "\n", 1);
  return 0;
}

int stupid_buffer_read(uint8_t *buff, int bytes) {
  if (buff == NULL) {
    return -1;
  }
  int length = read(STDIN, buff, bytes);
  if (length >= 0) {
    return length;
  } else {
    return -1;
  }
}

int stupid_random(int maximum, int minimum) {
  return (rand() % (maximum + 1 - minimum) + minimum);
}
