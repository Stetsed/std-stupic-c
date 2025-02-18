#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stupid.h>
#include <unistd.h>

float calculate_belasting(int money) {
  // 2D array that has instances of the diffrent belasting tiers, each having a
  // minimum(where it starts), maximum(where it ends), and the percentage as
  // defined as a factor, it will then loop over int and apply the relevant ones
  // to int money inserted.
  float belasting_tiers[3][3] = {
      {0, 38441, 0.3582}, {38441, 76817, 0.3748}, {76817, FLT_MAX, 0.495}};
  int rows = sizeof(belasting_tiers) / sizeof(belasting_tiers[0]);
  float belasting = 0;

  for (int i = 0; i < rows; i++) {
    if (money > belasting_tiers[i][1]) {
      belasting += (belasting_tiers[i][1] - belasting_tiers[i][0]) *
                   belasting_tiers[i][2];
    } else if (money > belasting_tiers[i][0]) {
      belasting += (money - belasting_tiers[i][0]) * belasting_tiers[i][2];
    }
  }
  return belasting;
}

void hoger_lager_spell() {

  char buffer[64];

  int chances = 4;
  stupid_println("Give minimum number:");
  int minimum = stupid_buffer_read(buffer, 64);

  stupid_println("Give maximum number:");
  int maximum = stupid_buffer_read(buffer, 64);

  int random = stupid_random(maximum, minimum);

  char output_buffer[64];
  while (chances > 0) {
    stupid_println("Give input:");
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

  float sum = 0;
  int minimum_grades = 0;
  int failed_grades = 0;
  float lowest_grade = 10;

  int cijfer_intake = grade_amount;
  while (cijfer_intake > 0) {
    stupid_println("Give your grade");
    stupid_buffer_read((char *)input_buffer, 60);
    float grade = atof(input_buffer);
    while (grade == 0) {
      stupid_println("Give your grade, because what you entered is invalid");
      stupid_buffer_read((char *)input_buffer, 60);
      grade = atof(input_buffer);
    }
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

  if (average <= voldoende || minimum_grades > 1 || failed_grades > 0) {
    stupid_println("You failed, try again next year");
    printf("Average: %0.1f\n", average);
    printf("Lowest Grade: %0.1f\n", lowest_grade);
  } else if (average >= average_lof && lowest_grade >= lowest_lof) {
    stupid_println("You passed with lof.. CONGRATS!!!");
    printf("Average: %0.1f\n", average);
    printf("Lowest Grade: %0.1f\n", lowest_grade);
  } else {
    stupid_println("You passed at normal parameters");
    printf("Average: %0.1f\n", average);
    printf("Lowest Grade: %0.1f\n", lowest_grade);
  }
}

typedef struct Player {
  int ThrowsAffect;
  int Points;
} Player;

void bowling_add_score(Player *player, int *scores, int throws) {
  for (int i = 0; i < throws; i++) {
    player->Points += (scores[i] + (scores[i] * player->ThrowsAffect));
    if (player->ThrowsAffect > 0) {
      player->ThrowsAffect--;
    }
  }
}

void bowling_special_frame(Player *player, int throws) {
  char input_buffer[64];
  int scores[throws];
  int throw_score = 0;
  for (int c = 0; c < throws; c++) {
    stupid_println("Give your score");
    stupid_buffer_read((char *)input_buffer, 60);
    int thrown = stupid_char_int((char *)input_buffer);
    scores[c] = thrown;
    throw_score += thrown;
  }

  bowling_add_score(player, scores, throws);

  if (throw_score >= 10) {
    stupid_println("Final special frame throw");
    stupid_buffer_read((char *)input_buffer, 60);
    int final_throw = stupid_char_int((char *)input_buffer);
    player->Points += final_throw;
  }
}

void bowling_game() {
  int throws = 2;
  int rounds = 10;
  int players = 1;
  char input_buffer[64];

  printf("Players: %d\nRounds: %d\nThrows: %d\n", players, rounds, throws);

  struct Player players_array[players];
  for (int i = 0; i < players; i++) {
    Player player = {0, 0};
    players_array[i] = player;
  }

  for (int a = 1; a <= rounds; a++) {
    printf("Round %d\n\n\n", a);
    // We are now in the loop for the amount of rounds there are in the game
    for (int b = 0; b < players; b++) {
      int knocked_pins = 0;
      printf("Player %d, score %d is up!\n", b, players_array[b].Points);
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
            players_array[b].Points +=
                10 + (10 * players_array[b].ThrowsAffect);
            players_array[b].ThrowsAffect += 1;
            if (players_array[b].ThrowsAffect >= 3) {
              players_array[b].ThrowsAffect = 2;
            }
            strike = true;
            break;
          } else {
            knocked_pins += throw_score;
          }
        }
        if (knocked_pins == 10 && !strike) {
          bowling_add_score(&players_array[b], scores, throws);
          stupid_println("SPARE!");
          players_array[b].ThrowsAffect += 1;
        } else if (!strike) {
          bowling_add_score(&players_array[b], scores, throws);
          stupid_println("OPEN!");
          players_array[b].ThrowsAffect += 0;
        }
      } else {
        bowling_special_frame(&players_array[b], throws);
      }
    }
  }
  stupid_println("THE GAME HAS FINISHED, THE SCORES ARE:");

  for (int i = 0; i < players; i++) {
    printf("Player %d, has a score of %d'\n", i, players_array[i].Points);
  }
}
