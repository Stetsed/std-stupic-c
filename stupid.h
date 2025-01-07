#include <stdio.h>
#include <unistd.h>

// NOLINTBEGIN
int stupid_strlen(char *string) {
  int counter = 0;
  for (; string[counter]; counter++)
    ;
  return counter;
}

int stupid_write_buffer(char *output) {
  write(fileno(stdout), output, stupid_strlen(output));
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
  int counter = 0;
  int returns = 0;
  int multiples = 0;
  int length = stupid_strlen(input);
  while (counter < length) {

    int possible_num = (int)(input[counter] - '0');
    if (possible_num < 9 || possible_num > 0) {
      returns += possible_num * (10 ^ multiples);
      counter++;
      multiples++;
    } else {
      break;
    }
  }
  return returns;
}

// NOLINTEND
