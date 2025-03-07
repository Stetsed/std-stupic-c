/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#define DEBUG

#include "stupid-net.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stupid-school.h>
#include <stupid-tcp.h>
#include <stupid.h>
#include <unistd.h>
#define EXIT_SUCCESS 0
#define ENTER 10

int main(int argc, char *argv[]) {
  random_teamlid_thingie();
  // TcpInstance instance = setup_tcp_instance();
  //
  // TcpConnection connection;
  // uint16_t port = 9283;
  // uint8_t addr[4] = {127, 0, 0, 1};
  // uint32_t address = stupid_bytes_to_address(addr);
  // bind_tcp_client(&instance);
  // connect_tcp_client(&instance, &connection, port, address);
  // char message[] = "Hello how you do bitch\n";
  // write_connection(&connection, message, sizeof(message));
  // close_connection(&connection);
}
