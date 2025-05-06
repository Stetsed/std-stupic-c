/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#include "stupid-unix.h"
#define DEBUG

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stupid.h>
#include <unistd.h>
#define EXIT_SUCCESS 0
#define ENTER 10

int main(int argc, char *argv[]) {
  stpunix_tcp_instance_s instance_i;
  stpunix_tcp_connection_s connection_i;
  stpunix_instance_init(&instance_i);
  int return_bind = stpunix_bind_tcp_serv(&instance_i, 0, 9999);
  stpunix_blocking_accept_connection_serv(&instance_i, &connection_i);

  while (1) {
    stpunix_write_connection(&connection_i, (uint8_t *)"Hello\n", 6);
  }
}
