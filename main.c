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

// TcpInstance instance = setup_tcp_instance();
//
// TcpConnection connection;
// uint16_t port = 9999;
// uint8_t addr[4] = {127, 0, 0, 1};
// uint32_t address = stupid_bytes_to_address(addr);
// bind_tcp_serv(&instance, port, address);
#ifdef SERVER
  server_program();
#endif /* ifdef SERVER */
#ifdef CLIENT
  client_program();
#endif /* ifdef CLIENT */
}
