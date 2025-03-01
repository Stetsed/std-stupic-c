/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stupid.h>
#include <unistd.h>

float calculate_belasting(int money) {
  // 2D array that has instances of the diffrent belasting tiers, each having a
  // minimum(where it starts), maximum(where it ends), and the percentage as
  // defined as a factor, it will then loop over int and apply the relevant ones
  // to int money inserted.
  const int rows = 3;
  float belasting_tiers[rows][3] = {
      {0, 38441, 0.3582}, {38441, 76817, 0.3748}, {76817, FLT_MAX, 0.495}};
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

void stupid_user_reading() {
  bool valid = false;
  int buff_size = 128;
  char buffer[buff_size];
  char output[buff_size];
  char output2[buff_size];

  while (!valid) {
    stupid_println("Enter your data in the format \"Key : Value\"");
    stupid_buffer_read((char *)buffer, 127);
    stupid_str_lowercase(buffer);
    int seperator_location = stupid_find_substring(buffer, ":");

    switch (buffer[0]) {
    case '"':
    case 'b':
      // To add fuel you just add them to the array, and make sure the length of
      // there name is not > than the second array size designator
      char valid_fuels[4][16] = {"benzine", "lpg", "diesel", "kerosine"};
      bool matched = false;

      for (int i = 0; i < sizeof(valid_fuels) / sizeof(valid_fuels[0]); i++) {

        int compare = stupid_strcmp_ignorec(buffer + seperator_location,
                                            valid_fuels[i], ": \"\n");
        if (compare == 0) {
          matched = true;
          printf("Brandstof being used is %s\n", valid_fuels[i]);
          valid = true;
          break;
        }
      }
      break;

    default:
      int temp_int = stupid_char_int_error(buffer + seperator_location);
      if (temp_int == -1) {
        stupid_println("Invalid value, retry");

      } else {
        stupid_strncpy(output, buffer, seperator_location - 1);
        printf("Value for \nKey: %s \n Value: %d\n", output, temp_int);
        valid = true;
      }
      break;
    };
  };
}

typedef enum state { Thuis, Uit } state;
typedef struct match {
  state status;
  int self_score;
  int opponent_score;
  char opponent[32];
} match;

typedef struct wedstrijd {
  int wedstrijden;
  int punten;
  int zelf_doelsaldo;
  int opponent_doelsaldo;
} wedstrijd;

void voetbal_score_inlezen() {
  char buffer[2048];
  char second_buffer[256];
  struct match matches[64] = {0};
  char *buffer_pointer = buffer;
  int match_counter = 0;
  FILE *fp = fopen("./voetbal.txt", "r");
  while (1) {
    char *fget_return = fgets(buffer, 2047, fp);
    stupid_str_lowercase(buffer);
    int minus_location = stupid_find_substring(buffer_pointer, "-");
    if (fget_return == NULL) {
      break;
    }
    switch (buffer_pointer[0]) {
    case 't':
      matches[match_counter].status = Thuis;
      // Getting the int after the "Thuis", which is score for own party.
      matches[match_counter].self_score =
          stupid_char_int(buffer + minus_location - 2);
      // Getting int after the : which is the score for the other party
      matches[match_counter].opponent_score =
          stupid_char_int(buffer + minus_location + 2);
      // Getting opponent name
      stupid_strcpy(matches[match_counter].opponent,
                    buffer + minus_location + 4);
      matches[match_counter]
          .opponent[stupid_strlen(matches[match_counter].opponent) - 1] = 0;
      printf("Status: %s \nOponnent: %s %d \nSelf: %d \n", "Thuis",
             matches[match_counter].opponent,
             matches[match_counter].opponent_score,
             matches[match_counter].self_score);

      match_counter++;
      break;

    case 'u':
      matches[match_counter].status = Uit;

      // Getting the int after the "Uit", which is score for other party.
      matches[match_counter].opponent_score =
          stupid_char_int(buffer + minus_location - 2);
      // Getting int after the : which is the score for the self party
      matches[match_counter].self_score =
          stupid_char_int(buffer + minus_location + 2);
      // Getting opponent name
      stupid_strcpy(matches[match_counter].opponent,
                    buffer + minus_location + 4);
      matches[match_counter]
          .opponent[stupid_strlen(matches[match_counter].opponent) - 1] = 0;
      printf("Status: %s \nOponnent: %s %d \nSelf: %d \n", "Uit",
             matches[match_counter].opponent,
             matches[match_counter].opponent_score,
             matches[match_counter].self_score);
      match_counter++;
      break;
    }
    stupid_println("------------");
  }

  struct wedstrijd wedstrijd_object = {0, 0, 0, 0};
  for (int i = 0; matches[i].opponent[0] != 0; i++) {
    wedstrijd_object.wedstrijden++;
    wedstrijd_object.zelf_doelsaldo += matches[i].self_score;
    wedstrijd_object.opponent_doelsaldo += matches[i].opponent_score;
  }
  wedstrijd_object.punten +=
      wedstrijd_object.zelf_doelsaldo + wedstrijd_object.opponent_doelsaldo;
  printf("Wedstrijden %d, %d punten, doelsaldo (%d - %d)\n",
         wedstrijd_object.wedstrijden, wedstrijd_object.punten,
         wedstrijd_object.zelf_doelsaldo, wedstrijd_object.opponent_doelsaldo);

  stupid_println("What party do you want to check?");
  stupid_buffer_read(buffer, 32);
  for (int i = 0; i < wedstrijd_object.wedstrijden; i++) {
    int compare = stupid_strcmp_ignorec(buffer, matches[i].opponent, " \":,\n");
    if (compare == 0) {
      if (matches[i].self_score > matches[i].opponent_score) {
        printf("Won against!");
        exit(0);
      } else if (matches[i].self_score < matches[i].opponent_score) {
        printf("Lost against!");
        exit(0);
      } else if (matches[i].self_score == matches[i].opponent_score) {
        printf("Even against!");
        exit(0);
      }
    }
  }
  stupid_println("Party was not played against sadly :(, maybe next season");
}
