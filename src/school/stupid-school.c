/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

// Header
#include <stupid-school.h>
//

#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stupid-net.h>
#include <stupid-tcp.h>
#include <stupid.h>
#include <sys/poll.h>
#include <threads.h>
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

void user_reading() {
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

void stupid_float_printing(float *array, int size) {
  printf("[ ");
  for (int i = 0; i < size; i++) {
    if (i != 0) {
      printf(",%.2f", array[i]);
    } else {
      printf("%.2f", array[i]);
    }
  }
  printf(" ]");
}
void gen_array_random_bs(int min, int max, int *int_array, int size) {
  for (int i = 0; i < size; i++) {
    int_array[i] = stupid_random(max, min);
  }
}

void random_array_bs() {
  srand(time(NULL));
  char buffer[64] = {0};

  stupid_println("Give Maximum");
  stupid_buffer_read(buffer, 32);
  int maximum = stupid_char_int(buffer);

  stupid_println("Give Minimum");
  stupid_buffer_read(buffer, 32);
  int minimum = stupid_char_int(buffer);

  stupid_println("How large do you want the arrays to be?");
  stupid_buffer_read(buffer, 32);
  int size = stupid_char_int(buffer);
  int *int_array = (int *)malloc(size * 4);
  int *int_array_2 = (int *)malloc(size * 4);
  gen_array_random_bs(minimum, maximum, int_array, size);
  gen_array_random_bs(minimum, maximum, int_array_2, size);

  printf("Index ");
  for (int i = 0; i < size; i++) {
    printf("%d ", i);
  }
  printf("\n");

  printf("Array1 ");
  for (int i = 0; i < size; i++) {
    printf("%d ", int_array[i]);
  }
  printf("\n");

  printf("Array2 ");
  for (int i = 0; i < size; i++) {
    printf("%d ", int_array_2[i]);
  }
  printf("\n");

  printf("Resultaat ");
  for (int i = 0; i < size; i++) {
    if (int_array[i] > int_array_2[i]) {
      printf("%d ", int_array[i]);
    } else {
      printf("%d ", int_array_2[i]);
    }
  }
  printf("\n");
  free(int_array);
  free(int_array_2);
}

typedef struct vak {
  char naam[20];
  int ECTS;
} vak;

void change_vak(vak *vakken, int amount) {
  char buffer[64];
  int name_size = sizeof(vakken[0].naam);

  stupid_println("Welke vak will je veranderen?(Index)");
  stupid_buffer_read(buffer, 32);

  int index = stupid_char_int(buffer);
  if (index < 0 || index > amount - 1) {
    stupid_println("Out of bounds");
    exit(1);
  }
  printf("Current values: %s %d\n", vakken[index].naam, vakken[index].ECTS);
  stupid_println("Nieuwe Naam");
  stupid_buffer_read(buffer, 32);

  stupid_strncpy(vakken[index].naam, buffer, name_size - 3);

  stupid_println("Nieuwe ECTS Punten");
  stupid_buffer_read(buffer, 32);
  int punten = stupid_char_int(buffer);
  vakken[index].ECTS = punten;
}

void change_vak_chosen(vak *vakk) {
  vak vaki = vakk[0];
  char buffer[64];
  int name_size = sizeof(vaki.naam);
  printf("Current values: %s %d\n", vaki.naam, vaki.ECTS);
  stupid_println("Nieuwe Naam");
  stupid_buffer_read(buffer, 32);

  stupid_strncpy(vaki.naam, buffer, name_size - 3);

  stupid_println("Nieuwe ECTS Punten");
  stupid_buffer_read(buffer, 32);
  int punten = stupid_char_int(buffer);
  vaki.ECTS = punten;
}

void random_vakken_dingen() {

  vak vakken[5] = {
      {"Ok", 10}, {"Okok", 20}, {"Okokok", 20}, {"Bruh", 69}, {"Brah", 420}};

  for (int i = 0; i < (sizeof(vakken) / sizeof(vak)); i++) {
    printf("Name: %s\n Digits: %d\n\n", vakken[i].naam, vakken[i].ECTS);
  }
  change_vak(vakken, (sizeof(vakken) / sizeof(vak)));
  for (int i = 0; i < (sizeof(vakken) / sizeof(vak)); i++) {
    printf("Name: %s\n Digits: %d\n\n", vakken[i].naam, vakken[i].ECTS);
  }
}

typedef struct teamlid {
  int id;
  char naam[20];
  char opleiding[20];
} teamlid;

void naam_generator(char *holder) {
  int random = stupid_random(8, 0);
  char namen[10][20] = {"John",  "Bob",    "Alice", "Claire", "Duco",
                        "Oscar", "Robert", "Quinn", "Erynn",  "Quinten"};
  stupid_strcpy(holder, namen[random]);
}

void opleiding_generator(char *holder) {
  int random = stupid_random(4, 0);
  char opleidingen[6][20] = {"VMBO", "MBO", "HBO", "WO", "PhD", "MD"};
  stupid_strcpy(holder, opleidingen[random]);
}

void opleidingen_zoek(teamlid *leden, char *opleiding_zoek, int count) {
  bool match_found = false;

  for (int i = 0; i < count; i++) {
    int match =
        stupid_strcmp_ignorec(leden[i].opleiding, opleiding_zoek, ": \"\n");
    if (match == 0) {
      printf("ID: %d\nNaam: %s\nOpleiding: %s\n", leden[i].id, leden[i].naam,
             leden[i].opleiding);
      match_found = true;
    }
  }
  if (!match_found) {
    stupid_println(
        "Niemand heeft deze opleiding of deze opleiding is niet geldig.");
  }
}

int teamlid_generate_id() {
  static int id_count = 1000;
  int current_id = id_count;
  id_count++;
  return current_id;
}

void random_teamlid_thingie() {
  srand(time(NULL));
  char buffer[64] = {0};
  stupid_println("Hoeveel teamleden will je?");
  stupid_buffer_read(buffer, 32);
  int count = stupid_char_int(buffer);

  teamlid *leden = (teamlid *)malloc(count * sizeof(teamlid));

  for (int i = 0; i < count; i++) {
    leden[i].id = teamlid_generate_id();
    naam_generator(leden[i].naam);
    opleiding_generator(leden[i].opleiding);
  }
  stupid_println("Welke opleiding will je naar zoeken?");
  stupid_buffer_read(buffer, 32);
  opleidingen_zoek(leden, buffer, count);
}

void client_program() {
  uint8_t buffer[512] = {0};
  struct pollfd terminal_poll = {
      STDIN_FILENO,
      POLLIN,
  };
  TcpInstance client = setup_tcp_instance();
  bind_tcp_client(&client);
  TcpConnection connection;
  uint8_t addr[4] = {127, 0, 0, 1};
  uint32_t address = stupid_bytes_to_address(addr);
  connect_tcp_client(&client, &connection, 9999, address);
  while (1) {
    if (poll(&connection.poll_descriptor, 1, 1)) {
      int bytes = read(connection.socketfd, buffer, sizeof(buffer) - 1);
      if (bytes > 0) {
        buffer[bytes] = 0;
        printf("%s", buffer);
      }
    }
    if (poll(&terminal_poll, 1, 1)) {
      int bytes = read(STDIN_FILENO, buffer, sizeof(buffer));
      if (bytes > 0) {
        write(connection.socketfd, buffer, bytes);
      }
    }
  }
}

void server_program() {
  uint8_t buffer[1024] = {0};

  TcpInstance instance = setup_tcp_instance();

  uint16_t port = 9999;
  uint8_t addr[4] = {127, 0, 0, 1};
  uint32_t address = stupid_bytes_to_address(addr);
  bind_tcp_serv(&instance, port, address);

  uint16_t connections = 0;

  uint16_t max_connections = 16;
  TcpConnection *connection_list[16] = {0};
  while (1) {
    printf("Passed loop, connections: %d\n", connections);
    if (poll(&instance.poll_descriptor, 1, 1)) {
      TcpConnection *new_connection = malloc(sizeof(TcpConnection));
      int connection_result = accept_connection(&instance, new_connection);

      bool hit = false;
      if (connection_result == NO_ERROR) {
        for (int i = 0; i < max_connections; i++) {
          if (connection_list[i] == 0) {
            connection_list[i] = new_connection;
            hit = true;
            connections++;
            break;
          }
        }
        if (!hit) {
          free(new_connection);
        }
      } else {
        free(new_connection);
      }
    }

    for (int i = 0; i < max_connections; i++) {
      if (!connection_list[i]) {
        continue;
      }
      if (connection_list[i]->Status == SocketError ||
          connection_list[i]->Status == SocketInactive ||
          poll(&connection_list[i]->poll_descriptor_r, 1, 1)) {
        free(connection_list[i]);
        connection_list[i] = 0;
        connections--;
        continue;
      }
      int poll_result = poll_connection(connection_list[i]);
      if (poll_result == 1) {
        int read_result =
            read_connection(connection_list[i], buffer, sizeof(buffer));
        if (read_result > 0) {
          write_connection(connection_list[i], buffer, read_result);
        }
      }
    }
  }
}
