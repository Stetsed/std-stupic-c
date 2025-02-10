// #include "./stupid-bindgen/bindings.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stupid-net.h>
#include <stupid.h>
#include <time.h>
#include <unistd.h>
#define EXIT_SUCCESS 0
#define ENTER 10

float calculate_belasting(int money) {
  float belasting = 0;
  if (money <= 38441) {
    belasting += money * 0.3582;
  } else {
    belasting += 38441 * 0.3582;
    if (money <= 76.817) {
      belasting += (money - 38441) * 0.3748;
    } else {
      belasting += 76817 - 38441;
      belasting += (money - 76817) * 0.495;
    }
  }
  return belasting;
}

void hoger_lager_spell() {

  srand(time(NULL));

  // Rand returns between 0 and RAND_MAX, if we want a number between 0 and 20
  // we need to constrain it to these numbers. We do this with the % operator,
  // this will remove anything that fits over our size. So for us we want a max
  // of 0 and a minimum of 0, this means we do % (20 + 1 - 0), this means that
  // we wait until our value is smaller than 21 aka 20 or smaller.
  int random = rand() % (500 + 1 - 0);

  int chances = 4;

  char buffer[64];
  char output_buffer[64];
  while (chances > 0) {
    stupid_println("Give input bitch:");
    int amount = stupid_buffer_read(buffer, 64);
    if (amount > 0) {
      int digit = stupid_char_int(buffer);
      if (digit == -1) {
        stupid_println("Invalid");
      } else if (digit == random) {
        stupid_println("YOU GOT IT");
        exit(0);
      } else if (digit > random) {
        stupid_println("Lower");
      } else if (digit < random) {
        stupid_println("Higher");
      }
      chances--;
    }
  }
  stupid_print("You did not get the answer, the answer was: ");
  stupid_int_char(output_buffer, random);
  stupid_print(output_buffer);
  stupid_println("");
}

int main(int argc, char *argv[]) {
  uint8_t hello[] = {255, 255, 255, 255};
  uint32_t okay = stupid_bytes_to_address(hello);
}
