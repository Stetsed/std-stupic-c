/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stupid.h>
#include <time.h>
#include <unistd.h>

float calculate_belasting(int money) {
  float belasting = 0;
  if (money <= 38441) {
    belasting += money * 0.3582;
  } else {
    belasting += 38441 * 0.3582;
    if (money <= 76.817) {
      belasting += (money - 38441) * 0.3748;
    } else {
      belasting += (76817 - 38441) * 0.3748;
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

void calculate_cijfer() {
  float minimum = 4;
  float voldoende = 5.5;
  float average_lof = 7.5;
  float lowest_lof = 7;
  int grade_amount = 6;

  int cijfers[grade_amount];

  char input_buffer[64];

  int sum = 0;
  int minimum_grades = 0;
  int failed_grades = 0;
  float lowest_grade = 10;

  int cijfer_intake = grade_amount;
  while (cijfer_intake > 0) {
    stupid_println("Give your grade");
    stupid_buffer_read((char *)input_buffer, 2);
    float grade = atof(input_buffer);
    // Switched to atof cuz I need floats right now, cba to implement this for
    // floats
    // int grade = stupid_char_int((char *)input_buffer);
    cijfers[cijfer_intake - 1] = grade;
    if (grade < minimum) {
      failed_grades += 1;
    }
    if (grade >= minimum && grade < voldoende) {
      minimum_grades += 1;
    }
    if (grade < lowest_grade) {
      lowest_grade = grade;
    }
    sum += grade;
    cijfer_intake--;
  }
  float average = stupid_average(sum, grade_amount);

  if (average < voldoende || minimum_grades > 1 || failed_grades > 0) {
    stupid_println("You failed, try again next year");
    printf("Average: %0.0f\n", average);
    printf("Lowest Grade: %0.0f\n", lowest_grade);
  } else if (average >= average_lof && lowest_grade >= lowest_lof) {
    stupid_println("You passed with lof.. CONGRATS!!!");
    printf("Average: %0.0f\n", average);
    printf("Lowest Grade: %0.0f\n", lowest_grade);
  } else {
    stupid_println("You passed at normal parameters");
    printf("Average: %0.0f\n", average);
    printf("Lowest Grade: %0.0f\n", lowest_grade);
  }
}

typedef enum throw_type {
  OPEN = 1,
  SPARE = 2,
  HALF_STRIKE = 2,
  STRIKE = 2
} throw_type;

typedef struct Player {
  throw_type ThrowType;
  int Points;
} Player;

void bowling_add_score(Player *player, int *scores, int throws) {
  for (int i = 0; i < throws; i++) {
    player->Points += (scores[i] * player->ThrowType);
    if (player->ThrowType == STRIKE) {
      player->ThrowType = HALF_STRIKE;
    } else {
      player->ThrowType = OPEN;
    }
  }
}

void bowling_bullshit() {
  int throws = 2;
  int rounds = 10;
  int players = 1;
  char input_buffer[64];

  printf("Players: %d\nRounds: %d\nThrows: %d\n", players, rounds, throws);

  struct Player players_array[players];
  for (int i = 0; i < players; i++) {
    Player player = {OPEN, 0};
    players_array[i] = player;
  }

  for (int a = 1; a <= rounds; a++) {
    printf("Round %d\n\n\n", a);
    // We are now in the loop for the amount of rounds there are in the game
    for (int b = 0; b < players; b++) {
      int knocked_pins = 0;
      printf("Player %d is up!\n", b);
      if (a != rounds) {
        // The loop for each players turn
        int scores[throws];
        bool strike = false;
        for (int c = 0; c < throws; c++) {
          stupid_println("Give your score");
          stupid_buffer_read((char *)input_buffer, 60);
          int throw_score = stupid_char_int((char *)input_buffer);
          scores[c] = throw_score;
          if (throw_score == 10 && c == 0) {
            stupid_println("STRIKE");
            players_array[b].Points += 10 * players_array[b].ThrowType;
            players_array[b].ThrowType = STRIKE;
            strike = true;
            break;
          } else {
            knocked_pins += throw_score;
          }
        }
        if (knocked_pins == 10 && !strike) {
          bowling_add_score(&players_array[b], scores, throws);
          stupid_println("SPARE!");
          players_array[b].ThrowType = SPARE;
        } else if (!strike) {
          bowling_add_score(&players_array[b], scores, throws);
          stupid_println("OPEN!");
          players_array[b].ThrowType = OPEN;
        }
      } else {
        int throw_score = 0;
        for (int c = 0; c < throws; c++) {
          stupid_println("Give your score");
          stupid_buffer_read((char *)input_buffer, 60);
          throw_score += stupid_char_int((char *)input_buffer);
        }

        if (throw_score == 20) {
          stupid_println("Final special frame throw");
          stupid_buffer_read((char *)input_buffer, 60);
          throw_score += stupid_char_int((char *)input_buffer);
        }
        players_array[b].Points += throw_score;
      }
    }
  }
  stupid_println("THE GAME HAS FINISHED, THE SCORES ARE:");

  for (int i = 0; i < players; i++) {
    printf("Player %d, has a score of %d'\n", i, players_array[i].Points);
  }
}
